
#include "definitions.h"
#include "RMCS2303drive.h"
#include "service_calls.h"

int main()
{
    stdio_init_all();

    // Initialize UART
    init_uart(UART_ID_Primary, BAUDRATE, UART_TX_PIN_Primary, UART_RX_PIN_Primary);

    // Initialize I2C   
    init_i2c(I2C_PORT, 100 * 1000, I2C_SDA_PIN, I2C_SCL_PIN);

    RMCS2303 rmcs2303;
    rmcs2303.Serial0(BAUDRATE);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
