#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C defines
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

// Gyroscope reading registers start address for BNO055
#define GYRO_START_REG 0x14
// Sensitivity factor for gyroscope data (LSB/dps)
#define GYRO_SENSITIVITY 16.0

static int addr = 0x28;

// Initialise Accelerometer Function
void accel_init(void){
    // Check to see if connection is correct
    sleep_ms(100); // Add a short delay to help BNO005 boot up
    uint8_t reg = 0x00;
    uint8_t chipID[1];
    int result = i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
    printf("Result: %d\n", result);
    i2c_read_blocking(I2C_PORT, addr, chipID, 1, false);

    if(chipID[0] != 0xA0){
        while(1){
            printf("Chip ID Not Correct - Check Connection!");
            sleep_ms(5000);
        }
    }

    // Use internal oscillator
    uint8_t data[2];
    data[0] = 0x3F;
    data[1] = 0x40;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Reset all interrupt status bits
    data[0] = 0x3F;
    data[1] = 0x01;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Configure Power Mode
    data[0] = 0x3E;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(50);

    // Default Axis Configuration
    data[0] = 0x41;
    data[1] = 0x24;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Default Axis Signs
    data[0] = 0x42;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);

    // Set units to m/s^2
    data[0] = 0x3B;
    data[1] = 0b0001000;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(30);

    // Set operation to acceleration only
    data[0] = 0x3D;
    data[1] = 0x0C;
    i2c_write_blocking(I2C_PORT, addr, data, 2, true);
    sleep_ms(100);
}

int main(void){
    stdio_init_all(); // Initialise STD I/O for printing over serial

    // Configure the I2C Communication
    i2c_init(I2C_PORT, 115200);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    sleep_ms(5000); // Add a short delay to help BNO005 boot up
    // Call accelerometer initialisation function
    accel_init();

    uint8_t accel[6]; // Store data from the 6 acceleration registers
    int16_t accelX, accelY, accelZ; // Combined 3 axis data
    float f_accelX, f_accelY, f_accelZ; // Float type of acceleration data
    uint8_t val = 0x08; // Start register address
    
    // Infinite Loop
    while(1){
        i2c_write_blocking(I2C_PORT, addr, &val, 1, true);
        i2c_read_blocking(I2C_PORT, addr, accel, 6, false);

        accelX = ((accel[1]<<8) | accel[0]);
        accelY = ((accel[3]<<8) | accel[2]);
        accelZ = ((accel[5]<<8) | accel[4]);
        
        f_accelX = accelX / 100.00;
        f_accelY = accelY / 100.00;
        f_accelZ = accelZ / 100.00;
        
        // Read gyroscope data
        uint8_t gyro[6];
        uint8_t gyro_reg = GYRO_START_REG;
        i2c_write_blocking(I2C_PORT, addr, &gyro_reg, 1, true);
        i2c_read_blocking(I2C_PORT, addr, gyro, 6, false);
        int16_t gyroX = ((int16_t)gyro[1] << 8) | gyro[0];
        int16_t gyroY = ((int16_t)gyro[3] << 8) | gyro[2];
        int16_t gyroZ = ((int16_t)gyro[5] << 8) | gyro[4];

        // Convert raw data to degrees per second (dps)
        float dpsX = gyroX / GYRO_SENSITIVITY;
        float dpsY = gyroY / GYRO_SENSITIVITY;
        float dpsZ = gyroZ / GYRO_SENSITIVITY;

        printf("Gyro -> X: %6.2f dps  Y: %6.2f dps  Z: %6.2f dps\n", dpsX, dpsY, dpsZ);
        // Print to serial monitor
        printf("X: %6.2f    Y: %6.2f    Z: %6.2f\n", f_accelX, f_accelY, f_accelZ);
        sleep_ms(100);
    }
}