#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pico/stdlib.h>
#include <pico/error.h>
#include <hardware/gpio.h>
#include <hardware/uart.h>
#include <hardware/irq.h>
#include <hardware/timer.h>
#include <hardware/i2c.h>
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"


// Communication pins
#define UART_ID_Primary uart0      // Reserved for motor driver
#define UART_ID_Secondary uart1
#define UART_TX_PIN_Primary 0      // Reserved for motor driver
#define UART_RX_PIN_Primary 1      // Reserved for motor driver
#define UART_TX_PIN_Secondary 4
#define UART_RX_PIN_Secondary 5

// UART baudrate
#define BAUDRATE 115200

#define I2C_PORT i2c0
#define I2C_SDA_PIN 2
#define I2C_SCL_PIN 3

// SPI Definitions
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19


// Toggle pins
#define LED_PIN 25
#define TOGG_PIN_1_M 15
#define TOGG_PIN_2_M 14
#define TOGG_PIN_3_M 13
#define TOGG_PIN_4_M 12

#define TOGG_PIN_1_S 11
#define TOGG_PIN_2_S 10

#define FORK_PIN 9


// Function prototypes
void init_uart(uart_inst_t *, uint, uint8_t, uint8_t);

#endif // DEFINITIONS_H