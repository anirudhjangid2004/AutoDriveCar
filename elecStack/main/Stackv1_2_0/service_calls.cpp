
#include "service_calls.h"
#include "definitions.h"

void init_uart(uart_inst_t *uart, uint baudrate, uint8_t tx_pin, uint8_t rx_pin){
    uart_init(uart, baudrate);
    gpio_set_function(tx_pin, GPIO_FUNC_UART);
    gpio_set_function(rx_pin, GPIO_FUNC_UART);
    uart_set_hw_flow(uart, false, false);
    uart_set_format(uart, 8, 1, UART_PARITY_NONE);
}

// Initializes the I2C bus
void init_i2c(i2c_inst_t *i2c, uint baudrate, uint8_t sda_pin, uint8_t scl_pin){
    i2c_init(i2c, 100 * 1000);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
}

// Initializes the SPI bus
void init_spi(spi_inst_t *spi, uint baudrate, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin, uint8_t cs_pin){
    spi_init(spi, baudrate);
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(cs_pin, GPIO_FUNC_SIO);
    gpio_set_dir(cs_pin, GPIO_OUT);
    gpio_put(cs_pin, 1);
}

// Initializes the GPIO pins
bool init_gpio(){
    gpio_init(LED_PIN);
    gpio_init(FORK_PIN);
    gpio_init(TOGG_PIN_1_M);
    gpio_init(TOGG_PIN_2_M);
    gpio_init(TOGG_PIN_3_M);
    gpio_init(TOGG_PIN_4_M);
    gpio_init(TOGG_PIN_1_S);
    gpio_init(TOGG_PIN_2_S);

    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(FORK_PIN, GPIO_OUT);
    gpio_set_dir(TOGG_PIN_1_M, GPIO_OUT);
    gpio_set_dir(TOGG_PIN_2_M, GPIO_OUT);
    gpio_set_dir(TOGG_PIN_3_M, GPIO_OUT);
    gpio_set_dir(TOGG_PIN_4_M, GPIO_OUT);
    gpio_set_dir(TOGG_PIN_1_S, GPIO_OUT);
    gpio_set_dir(TOGG_PIN_2_S, GPIO_OUT);

    return true;    
}

// Set the state of a GPIO pin
void set_gpio(uint8_t pin, bool state){
    gpio_put(pin, state);
}

// Toggle the state of a GPIO pin
void toggle_gpio(uint8_t pin){
    gpio_put(pin, !gpio_get(pin));
}
