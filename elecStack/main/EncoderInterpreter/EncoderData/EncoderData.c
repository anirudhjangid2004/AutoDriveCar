#include "EncoderData.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

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
    pwm_set_wrap(slice_num, 12500 - 1); // 1 kHz frequency with 125MHz clock
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), duty_cycle * 12500);
    pwm_set_enabled(slice_num, true); // Enable PWM
}

/*
    Interrupt Service Routine for measuring time period between two rising edges
    Measures time period between two rising edges of the encoder
    Writes the time period to TimePeriod array
    Writes the number of encoder waves to REVOLUTIONS array

    @param gpio: GPIO pin number for interrupt
    @param events: Events that triggered the interrupt
*/
void gpio_callback_channel(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_RISE) {
        uint64_t timestamp = time_us_64();

        if(gpio == EDGE_GPIO_A){
            if(log_value_A) {
                TimeStamp[0][0] = timestamp;
                log_value_A = false;
            }
            else if (!log_value_A) {
                REVOLUTIONS[0] += 1;
                TimeStamp[0][1] = timestamp;
                log_value_A = true;
            }
        }
        
        if(gpio == EDGE_GPIO_B){
            if(log_value_B) {
                TimeStamp[1][0] = timestamp;
                log_value_B = false;
            }
            else if (!log_value_B){
                TimeStamp[1][1] = timestamp;
                log_value_B = true;
                REVOLUTIONS[1] += 1;
            }
        }
    }
    if(TimeStamp[0][1] > TimeStamp[0][0]){
        TimePeriod[0] = TimeStamp[0][1] - TimeStamp[0][0];
    }
    if(TimeStamp[1][1] > TimeStamp[1][0]){
        TimePeriod[1] = TimeStamp[1][1] - TimeStamp[1][0];
    }
}



int main() {
    stdio_init_all();

    gpio_init(EDGE_GPIO_A);
    gpio_set_dir(EDGE_GPIO_A, GPIO_IN);
    gpio_pull_down(EDGE_GPIO_A);

    gpio_init(EDGE_GPIO_B);
    gpio_set_dir(EDGE_GPIO_B, GPIO_IN);
    gpio_pull_down(EDGE_GPIO_B);

    gpio_set_irq_enabled_with_callback(EDGE_GPIO_A, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel);
    gpio_set_irq_enabled_with_callback(EDGE_GPIO_B, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel);

    uint8_t i = 0;

    // Start motor with 50% duty cycle
    start_motor(MOTOR_PIN_A, MOTOR_PIN_B);
    // variable_speed(MOTOR_PIN_A, MOTOR_PIN_B, 25.0);
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    float duty_cycle = 0.1; // 50% duty cycle

    while (1) {
        set_pwm(PWM_PIN, duty_cycle);
        printf("TimePeriod A: %llu us ", TimePeriod[0]);
        printf("                      ");
        printf("TimePeriod B: %llu us\n", TimePeriod[1]);
        if(i == 10){
            printf("TimePeriod A: %llu us ", TimePeriod[0]);
            printf("Revolutions A: %u      ", REVOLUTIONS[0]);
            printf("TimePeriod B: %llu us ", TimePeriod[1]);
            printf("Revolutions B: %u\n", REVOLUTIONS[1]);
            i = 0;
            duty_cycle += 0.02;
        } 
        i++;
        sleep_ms(500);
    }

    return 0;
}
