#include "imuDriver.h"
#include "EncoderData.h"
#include "pinPlan.h"
#include "motorDriver.h"
#include "usbDriver.h"


void finish_init(void) {
    // Initialize the IMU
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    push_message("INITIALIZATION FINISH...............NEAT\n");
}

/*
    Hardware Timer ISR, sets the received PWM
    values to the respective PWM pins
    @param t: Timer instance
    @return: true
*/
bool timer_callback(repeating_timer_t *t) {
    // if (allocate_pwm) {
    //     // push_message("Timer callback, allocating pwm\n");
    //     set_pwm(PWM_PIN_1, pwmValues[0]);
    //     set_pwm(PWM_PIN_2, pwmValues[1]);
    //     set_pwm(PWM_PIN_3, pwmValues[2]);
    //     set_pwm(PWM_PIN_4, pwmValues[3]);
    // }


    // sendUSBMessage(TUSB_MSG_ID_ENCODER, (uint8_t *)REVOLUTIONS, 16);
    // sendUSBMessage(TUSB_MSG_ID_IMU, (uint8_t *)imuValue, 4);
    return true;
}

/*
    Function to initialize the encoder output pins
    According to pins defined in pinPlan.h
*/
void init_interrupt_pins(){
    gpio_init(EDGE_GPIO_1);
    gpio_init(EDGE_GPIO_2);
    gpio_init(EDGE_GPIO_3);
    gpio_init(EDGE_GPIO_4);
    gpio_set_dir(EDGE_GPIO_1, GPIO_IN);
    gpio_set_dir(EDGE_GPIO_2, GPIO_IN);
    gpio_set_dir(EDGE_GPIO_3, GPIO_IN);
    gpio_set_dir(EDGE_GPIO_4, GPIO_IN);
    gpio_pull_down(EDGE_GPIO_1);
    gpio_pull_down(EDGE_GPIO_2);
    gpio_pull_down(EDGE_GPIO_3);
    gpio_pull_down(EDGE_GPIO_4);
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

        if(gpio == EDGE_GPIO_1){
            if(log_value_1) {
                TimeStamp[0][0] = timestamp;
                log_value_1 = false;
            }
            else if (!log_value_1) {
                REVOLUTIONS[0] += 1;
                TimeStamp[0][1] = timestamp;
                log_value_1 = true;
            }
        }
        
        if(gpio == EDGE_GPIO_2){
            if(log_value_2) {
                TimeStamp[1][0] = timestamp;
                log_value_2 = false;
            }
            else if (!log_value_2){
                TimeStamp[1][1] = timestamp;
                log_value_2 = true;
                REVOLUTIONS[1] += 1;
            }
        }

        if(gpio == EDGE_GPIO_3){
            if(log_value_3) {
                TimeStamp[2][0] = timestamp;
                log_value_3 = false;
            }
            else if (!log_value_3){
                TimeStamp[2][1] = timestamp;
                log_value_3 = true;
                REVOLUTIONS[1] += 1;
            }
        }

        if(gpio == EDGE_GPIO_4){
            if(log_value_4) {
                TimeStamp[3][0] = timestamp;
                log_value_4 = false;
            }
            else if (!log_value_4){
                TimeStamp[3][1] = timestamp;
                log_value_4 = true;
                REVOLUTIONS[3] += 1;
            }
        }
    }
    if(TimeStamp[0][1] > TimeStamp[0][0]){
        TimePeriod[0] = TimeStamp[0][1] - TimeStamp[0][0];
    }
    if(TimeStamp[1][1] > TimeStamp[1][0]){
        TimePeriod[1] = TimeStamp[1][1] - TimeStamp[1][0];
    }
    if(TimeStamp[2][1] > TimeStamp[2][0]){
        TimePeriod[2] = TimeStamp[2][1] - TimeStamp[2][0];
    }
    if(TimeStamp[3][1] > TimeStamp[3][0]){
        TimePeriod[3] = TimeStamp[3][1] - TimeStamp[3][0];
    }
}

/*
    Function to bind interrupts to GPIO pins
    Binds interrupts to GPIO pins for encoder channels
*/
void bind_encoder_interrupts(void){
    gpio_set_irq_enabled_with_callback(EDGE_GPIO_1, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel);
    gpio_set_irq_enabled_with_callback(EDGE_GPIO_2, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel);
    gpio_set_irq_enabled_with_callback(EDGE_GPIO_3, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel);
    gpio_set_irq_enabled_with_callback(EDGE_GPIO_4, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel);
}

// /*
//     USB Interrupt Service Routine
//     Reads the USB buffer and processes the message
// */
// void usb_callback() {
//     readUSBBuffer();
// }


int main() {

    // Initialize stdio
    stdio_init_all();


    sleep_ms(8000); // To test


    // Initialize TinyUSB stack
    tusb_init();

    while (!tud_mounted()) {
        sleep_ms(10);  // Wait for host connection
    }
    
    push_message("********* STACK UP AND RUNNING!!! **********\n");
    push_message("USB Initialized.....................NEAT\n");

    repeating_timer_t timer;
    // bool timer_started = add_repeating_timer_ms(100, timer_callback, NULL, &timer);
    bool timer_started = false;
    if(timer_started) push_message("Timer started.......................NEAT\n");
    else push_message("Timer not started..................ERROR\n");

    // Initialize all the pins
    init_motor_pins();
    set_motor_dirn();
    push_message("Motor pins initialized..............NEAT\n");
    sleep_ms(100);
    init_interrupt_pins();
    push_message("Interrupt pins initialized..........NEAT\n");
    sleep_ms(100);
    init_pwm_pins();
    push_message("PWM pins initialized................NEAT\n");
    sleep_ms(2);

    // Bind the encoder pins to interrupts
    bind_encoder_interrupts();
    push_message("Encoder interrupts bound............NEAT\n");
    sleep_ms(500);

    // Initialize the IMU
    imu_init();
    push_message("IMU initialized.....................NEAT\n");
    sleep_ms(1000); // Long enough to boot the IMU

    push_message("Ready to take input!................NEAT\n");
    sleep_ms(200);

    finish_init();

    uint8_t i = 0;
    // uint8_t j = 0;

    while (true) {
        tud_task(); // tinyusb device task
        readUSBBuffer();
        // tight_loop_contents();
        // if(j == 100){
        //     // for(int i = 0; i < 4; i++){
        //     //     printf("Motor %d: %lu\n", i, pwmValues[i]);
        //     // }

        //     printf("Accel -> X: %6.2f dps  Y: %6.2f dps  Z: %6.2f dps\n", accel_final[0]/100.00, accel_final[1]/100.00, accel_final[2]/100.00);
        //     // Print to serial monitor
        //     // printf("X: %6.2f    Y: %6.2f    Z: %6.2f\n", f_accelX, f_accelY, f_accelZ);

        //     j = 0;
        // }
        // j++;

        if(i == 10){
            set_pwm(PWM_PIN_1, pwmValues[0]);
            set_pwm(PWM_PIN_2, pwmValues[1]);
            set_pwm(PWM_PIN_3, pwmValues[2]);
            set_pwm(PWM_PIN_4, pwmValues[3]);
            
            get_accel();
            get_gyro();
            i = 0;
        }
        i++;

        sleep_ms(5);
    }

    return 0;
}