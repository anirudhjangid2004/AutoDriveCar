#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t TimeStamp[2][2] = {{0, 0}, {0, 0}};
uint64_t TimePeriod[2] = {0, 0};

uint32_t REVOLUTIONS[2] = {0, 0};

#define PWM_PERIOD_US 1000 // 1 kHz frequency

#define PWM_PIN_1 18      // GPIO pin for PWM output
#define MOTOR_PIN_1_A 16  // GPIO pin for motor control A
#define MOTOR_PIN_1_B 17  // GPIO pin for motor control B
#define EDGE_GPIO_1_A 19  // GPIO pin for encoder channel A
#define EDGE_GPIO_1_B 20  // GPIO pin for encoder channel B

#define PWM_PIN_2 1      // GPIO pin for PWM output
#define MOTOR_PIN_2_A 2  // GPIO pin for motor control A
#define MOTOR_PIN_2_B 3  // GPIO pin for motor control B
#define EDGE_GPIO_2_A 4  // GPIO pin for encoder channel A
#define EDGE_GPIO_2_B 5  // GPIO pin for encoder channel B

#define PWM_PIN_3 6      // GPIO pin for PWM output
#define MOTOR_PIN_3_A 7  // GPIO pin for motor control A
#define MOTOR_PIN_3_B 8  // GPIO pin for motor control B
#define EDGE_GPIO_3_A 9  // GPIO pin for encoder channel A
#define EDGE_GPIO_3_B 10  // GPIO pin for encoder channel B

#define PWM_PIN_4 11      // GPIO pin for PWM output
#define MOTOR_PIN_4_A 12  // GPIO pin for motor control A
#define MOTOR_PIN_4_B 13  // GPIO pin for motor control B
#define EDGE_GPIO_4_A 14  // GPIO pin for encoder channel A
#define EDGE_GPIO_4_B 15  // GPIO pin for encoder channel B

bool log_value_A = true;
bool log_value_B = true;
bool run = true;