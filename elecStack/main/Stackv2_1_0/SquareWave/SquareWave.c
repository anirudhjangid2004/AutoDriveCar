#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SYS_CLOCK 125000000

/*
    Generate Square wave for motor driver
    @param pinA: GPIO pin number for motor pin A
    @param pinB: GPIO pin number for motor pin B
    @param duty_cycle: Duty cycle for PWM
*/
void generate_square_wave(uint gpio, uint32_t frequency, uint8_t duty_cycle) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    // uint32_t wrap_value = (SYS_CLOCK / frequency) - 1;
    uint32_t wrap_value = 100;
    // uint32_t level = (duty_cycle * wrap_value) / 100;

    // PWM setup
    pwm_set_wrap(slice_num, wrap_value);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), duty_cycle);
    pwm_set_enabled(slice_num, true); 
    printf("GPIO: %d, Slice: %d, Freq: %lu Hz, Duty: %u%%, Wrap: %lu \n",
        gpio, slice_num, frequency, duty_cycle, wrap_value);
}


int main()
{
    stdio_init_all();

    sleep_ms(9000);

    generate_square_wave(0, 1000, 50);
    generate_square_wave(2, 1000, 50);

    gpio_init(3);
    gpio_set_dir(3, GPIO_OUT);
    gpio_put(3, 1);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
