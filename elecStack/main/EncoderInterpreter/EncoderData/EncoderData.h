#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t TimeStamp[2][2] = {{0, 0}, {0, 0}};
uint64_t TimePeriod[2] = {0, 0};



#define EDGE_GPIO_A 14
#define EDGE_GPIO_B 15

bool log_value_A = true;
bool log_value_B = true;