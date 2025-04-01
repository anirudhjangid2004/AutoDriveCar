#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "tusb.h"
#include "hardware/irq.h"
#include "hardware/regs/usb.h"
#include "hardware/structs/usb.h"
#include "hardware/timer.h"

// #define PWM_PERIOD_US 1000 // 1 kHz frequency

uint64_t TimeStamp[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
uint64_t TimePeriod[4] = {0, 0, 0, 0};
uint32_t REVOLUTIONS[4] = {0, 0, 0, 0};

bool kill_me = false;

bool log_value_1 = true;
bool log_value_2 = true;
bool log_value_3 = true;
bool log_value_4 = true;

void gpio_callback_channel(uint, uint32_t);
void bind_encoder_interrupts(void);
void init_interrupt_pins(void);
