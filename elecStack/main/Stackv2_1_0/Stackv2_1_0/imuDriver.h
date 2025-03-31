#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

// #include "EncoderData.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pinPlan.h"
#include "usbDriver.h"


#define GYRO_START_REG 0x14 
#define GYRO_SENSITIVITY 16.0

static int IMU_ADDR = 0x28;

uint8_t accel_interim[6] = {0};
int16_t accel_final[3]   = {0};
float   accel_float[3]   = {0}; 

uint8_t gyro_interim[6] = {0};
uint16_t gyro_final[3] = {0};

uint8_t val = 0x08; // Start register address
uint8_t gyro_addr = GYRO_START_REG;

// Initialise Accelerometer
void accel_init(void){
    
    sleep_ms(100); 
    uint8_t reg = 0x00;
    uint8_t chipID[1];
    int result = i2c_write_blocking(I2C_PORT, IMU_ADDR, &reg, 1, true);
    printf("Result: %d\n", result);
    i2c_read_blocking(I2C_PORT, IMU_ADDR, chipID, 1, false);

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
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);

    // Reset all interrupt status bits
    data[0] = 0x3F;
    data[1] = 0x01;
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);

    // Configure Power Mode
    data[0] = 0x3E;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);
    sleep_ms(50);

    // Default Axis Configuration
    data[0] = 0x41;
    data[1] = 0x24;
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);

    // Default Axis Signs
    data[0] = 0x42;
    data[1] = 0x00;
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);

    // Set units to m/s^2
    data[0] = 0x3B;
    data[1] = 0b0001000;
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);
    sleep_ms(30);

    // Set operation to acceleration only
    data[0] = 0x3D;
    data[1] = 0x0C;
    i2c_write_blocking(I2C_PORT, IMU_ADDR, data, 2, true);
    sleep_ms(100);
}

void imu_init(){

    // Initiate I2C bus for IMU
    i2c_init(I2C_PORT, 115200);
    gpio_set_function(IMU_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(IMU_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(IMU_I2C_SDA);
    gpio_pull_up(IMU_I2C_SCL);

    accel_init(); // Initialise accelerator
}

void get_accel(void){
    
    // push_message("Getting Accelerometer Data\n");
    i2c_write_blocking(I2C_PORT, IMU_ADDR, &val, 1, true);
    i2c_read_blocking(I2C_PORT, IMU_ADDR, accel_interim, 6, false);

    for(int i = 0; i < 3; i += 1){
        accel_final[i] = ((accel_interim[2*i + 1] << 8) | accel_interim[i*2]);
    }
}

void get_gyro(void){

    // push_message("Getting Gyroscope Data\n");
    i2c_write_blocking(I2C_PORT, IMU_ADDR, &gyro_addr, 1, true);
    i2c_read_blocking(I2C_PORT, IMU_ADDR, gyro_interim, 6, false);

    for(int i = 0; i < 3; i += 1){
        gyro_final[i] = ((gyro_interim[2*i + 1] << 8) | gyro_interim[i*2]);
    }
}

#endif