#ifndef PINPLAN_H
#define PINPLAN_H

#pragma once

#define PWM_PIN_1 0     // GPIO pin for PWM output
#define MOTOR_PIN_1_A 1  // GPIO pin for motor control A
#define MOTOR_PIN_1_B 2  // GPIO pin for motor control B
#define EDGE_GPIO_1   3  // GPIO pin for encoder channel A


#define PWM_PIN_2 16      // GPIO pin for PWM output
#define MOTOR_PIN_2_A 17  // GPIO pin for motor control A
#define MOTOR_PIN_2_B 6  // GPIO pin for motor control B
#define EDGE_GPIO_2   7  // GPIO pin for encoder channel A


#define PWM_PIN_3 8      // GPIO pin for PWM output
#define MOTOR_PIN_3_A 9  // GPIO pin for motor control A
#define MOTOR_PIN_3_B 10  // GPIO pin for motor control B
#define EDGE_GPIO_3   11  // GPIO pin for encoder channel A


#define PWM_PIN_4 12      // GPIO pin for PWM output
#define MOTOR_PIN_4_A 13  // GPIO pin for motor control A
#define MOTOR_PIN_4_B 14  // GPIO pin for motor control B
#define EDGE_GPIO_4   15  // GPIO pin for encoder channel A

#define I2C_PORT i2c0
#define IMU_I2C_SDA 4
#define IMU_I2C_SCL 5

#define LED_PIN 25

#endif