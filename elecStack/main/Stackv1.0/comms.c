
#include "definitions.h"

void init_uart(uart_inst_t *uart, uint baudrate, uint tx_pin, uint rx_pin){
    uart_init(uart, baudrate);
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);

    uart_set_hw_flow(uart, false, false);
}