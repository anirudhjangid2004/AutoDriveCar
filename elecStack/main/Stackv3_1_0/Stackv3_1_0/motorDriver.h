#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pinPlan.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PWM_PERIOD_US 1000 // 1 kHz frequency
#define SYS_CLOCK 125000000 // 125 MHz

bool allocate_pwm = true;
bool initial_set = true;

bool dirn[4] = {true, true, true, true};

void init_motor(uint , uint);
void dirn_motor(uint , uint, bool);
uint32_t set_pwm(uint , uint8_t);
void init_motor_pins(void);
void init_pwm_pins(void);

/*
    Function to initialize the motor pins
    @param pinA: GPIO pin number for motor pin A
    @param pinB: GPIO pin number for motor pin B

*/
void init_motor(uint pinA, uint pinB){
    gpio_init(pinA);
    gpio_init(pinB);
    gpio_set_dir(pinA, GPIO_OUT);
    gpio_set_dir(pinB, GPIO_OUT);
}

/*
    Function to change direction of the motor
    @param pinA: GPIO pin number for motor pin A
    @param pinB: GPIO pin number for motor pin B
    @param dirn: Direction of the motor (true for forward, false for reverse)
*/
void dirn_motor(uint pinA, uint pinB, bool dirn){
    if(dirn){
        gpio_put(pinA, 1);
        gpio_put(pinB, 0);
    }
    else{
        gpio_put(pinA, 0);
        gpio_put(pinB, 1);
    }
}

/*
    Function to set pwm for Enable pin of Motor Driver
    @param gpio: GPIO pin number for PWM
    @param duty_cycle: Duty cycle for PWM
*/
uint32_t set_pwm(uint gpio, uint8_t duty_cycle) {
    
    // if(duty_cycle <= 5){
    //     gpio_put(gpio, 0);
    //     return;
    // }
    // else if (duty_cycle >= 100)
    // {
    //     gpio_put(gpio, 1);
    //     return;
    // }

    if (duty_cycle >= 100)
    {
        duty_cycle = 100;
    }
    
    uint slice_num;
    uint wrap_value;

    slice_num = pwm_gpio_to_slice_num(gpio);
    wrap_value = 10000; 
    pwm_set_wrap(slice_num, wrap_value); // 1 kHz frequency with 125MHz clock


    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), duty_cycle*wrap_value/100);
    pwm_set_enabled(slice_num, true); // Enable PWM

    return 0;
}

/*
    Generate Square wave for motor driver
    @param pinA: GPIO pin number for motor pin A
    @param pinB: GPIO pin number for motor pin B
    @param duty_cycle: Duty cycle for PWM
*/
void generate_square_wave(uint gpio, uint32_t frequency, uint8_t duty_cycle) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t wrap_value = (SYS_CLOCK / frequency) - 1;
    uint32_t level = (duty_cycle * wrap_value) / 100;

    // PWM setup
    pwm_set_wrap(slice_num, wrap_value);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), level);
    pwm_set_enabled(slice_num, true); // PWM enable karna
    printf("GPIO: %d, Slice: %d, Freq: %lu Hz, Duty: %u%%, Wrap: %lu, Level: %lu\n",
        gpio, slice_num, frequency, duty_cycle, wrap_value, level);

    return;
}

/*
    Initialises all the motor pins
    According to pins defined in pinPlan.h
*/
void init_motor_pins(void){
    init_motor(MOTOR_PIN_1_A, MOTOR_PIN_1_B);
    init_motor(MOTOR_PIN_2_A, MOTOR_PIN_2_B);
    init_motor(MOTOR_PIN_3_A, MOTOR_PIN_3_B);
    init_motor(MOTOR_PIN_4_A, MOTOR_PIN_4_B);
}


/*
    Function to initialize the PWM pins
    According to pins defined in pinPlan.h
*/
void init_pwm_pins(){
    gpio_init(PWM_PIN_1);
    gpio_init(PWM_PIN_2);
    gpio_init(PWM_PIN_3);
    gpio_init(PWM_PIN_4);
    gpio_set_dir(PWM_PIN_1, GPIO_OUT);
    gpio_set_dir(PWM_PIN_2, GPIO_OUT);
    gpio_set_dir(PWM_PIN_3, GPIO_OUT);
    gpio_set_dir(PWM_PIN_4, GPIO_OUT);
    gpio_set_function(PWM_PIN_1, GPIO_FUNC_PWM);
    gpio_set_function(PWM_PIN_2, GPIO_FUNC_PWM);
    gpio_set_function(PWM_PIN_3, GPIO_FUNC_PWM);
    gpio_set_function(PWM_PIN_4, GPIO_FUNC_PWM);
}


void set_motor_dirn(){
    dirn_motor(MOTOR_PIN_1_A, MOTOR_PIN_1_B, dirn[0]);
    dirn_motor(MOTOR_PIN_2_A, MOTOR_PIN_2_B, dirn[1]);
    dirn_motor(MOTOR_PIN_3_A, MOTOR_PIN_3_B, dirn[2]);
    // dirn_motor(MOTOR_PIN_3_A, MOTOR_PIN_3_B, true);
    dirn_motor(MOTOR_PIN_4_A, MOTOR_PIN_4_B, dirn[3]);
}

#endif