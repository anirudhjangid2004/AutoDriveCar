#include "EncoderData.h"
#include "pinPlan.h"
#include "motorDriver.h"
#include "usbDriver.h"


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

void usb_irq_handler(void) {
    readUSBBuffer();
}

int main() {

    // Initialize stdio
    stdio_init_all();

    // Initialize all the pins
    init_motor_pins();
    init_interrupt_pins();
    init_pwm_pins();

    // Initialize TinyUSB stack
    tusb_init();

    // Enable USB IRQ
    irq_set_exclusive_handler(USBCTRL_IRQ, usb_irq_handler);
    irq_set_enabled(USBCTRL_IRQ, true);

    // Bind the encoder pins to interrupts
    bind_encoder_interrupts();

    while (allocate_pwm) {
        printf("TimePeriod A: %llu us ", TimePeriod[0]);
        printf("                      ");
        printf("TimePeriod B: %llu us\n", TimePeriod[1]);
        sleep_ms(500);
    }

    return 0;
}
