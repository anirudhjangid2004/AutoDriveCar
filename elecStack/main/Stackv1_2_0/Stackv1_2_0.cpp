
#include "definitions.h"
#include "RMCS2303drive.h"
#include "service_calls.h"

int main()
{
    stdio_init_all();

    init_uart(UART_ID_Secondary, BAUDRATE, UART_TX_PIN_Secondary, UART_RX_PIN_Secondary);

    // Initialize I2C   
    init_i2c(I2C_PORT, 100 * 1000, I2C_SDA_PIN, I2C_SCL_PIN);

    RMCS2303 rmcs2303;
    rmcs2303.Serial0(BAUDRATE);
    // const char* message = "Message over UART\n";

    while (true) {
        printf("Sending messages for motor drivers\n");
        sleep_ms(6000);

        bool once = true;
        printf("Sleep over\n");
            
        rmcs2303.Enable_Digital_Mode(1, 1);


        printf("Message sent\n");

        sleep_ms(1000);
    }
}
