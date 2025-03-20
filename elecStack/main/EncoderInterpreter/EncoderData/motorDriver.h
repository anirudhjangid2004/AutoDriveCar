#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PWM_PERIOD_US 1000 // 1 kHz frequency

void init_motor(uint , uint);
void dirn_motor(uint , uint, bool);
void set_pwm(uint , float);
void init_motor_pins(void);


