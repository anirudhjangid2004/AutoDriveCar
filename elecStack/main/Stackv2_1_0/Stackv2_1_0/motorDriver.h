#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pinPlan.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PWM_PERIOD_US 1000 // 1 kHz frequency

bool allocate_pwm = true;

void init_motor(uint , uint);
void dirn_motor(uint , uint, bool);
void set_pwm(uint , float);
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
void set_pwm(uint gpio, float duty_cycle) {
    
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, (125*100000/PWM_PERIOD_US) - 1); // 1 kHz frequency with 125MHz clock
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), duty_cycle * (125*100000/PWM_PERIOD_US));
    pwm_set_enabled(slice_num, true); // Enable PWM
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