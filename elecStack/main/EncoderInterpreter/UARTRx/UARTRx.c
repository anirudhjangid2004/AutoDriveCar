#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define LED_PIN 1

int main()
{
    stdio_init_all();

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_init(LED_PIN);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Set the LED pin high
    gpio_put(LED_PIN, 1);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
        bool state = gpio_get(LED_PIN);
        gpio_put(LED_PIN, !state);
    }
    // while(1){

    //     gpio_put(LED_PIN, 1);
    //     while(uart_is_readable(UART_ID)) {
    //         uint8_t ch = uart_getc(UART_ID);
    //         printf("Received: %c\n", ch);
    //     }

    //     printf("Done, no more data in uart\n");
    //     gpio_put(LED_PIN, 0);
    //     sleep_ms(1000);
    // }
}
