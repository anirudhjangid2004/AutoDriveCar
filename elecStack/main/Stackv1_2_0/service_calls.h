#ifndef SERVICE_CALLS_H
#define SERVICE_CALLS_H

#include <stdint.h>
#include <stdbool.h>
#include <pico/stdlib.h>
#include "definitions.h"

void init_uart(uart_inst_t *, uint, uint8_t, uint8_t);
void init_i2c(i2c_inst_t *, uint, uint8_t, uint8_t);
void init_spi(spi_inst_t *, uint, uint8_t, uint8_t, uint8_t, uint8_t);
bool init_gpio();
void set_gpio(uint8_t, bool);
void toggle_gpio(uint8_t);

#endif // SERVICE_CALLS_H
