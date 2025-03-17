#include "EncoderData.h"

uint32_t REVOLUTIONS[2] = {0, 0};

void gpio_callback_channel_A(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_RISE) {

        uint64_t timestamp = time_us_64();

        if(log_value_A) {
            TimeStamp[0][0] = timestamp;
            printf("ME entering log true \n");
            log_value_A = !log_value_A;
        }
        else if (!log_value_A) {
            printf("ME entering \n");
            REVOLUTIONS[0] = REVOLUTIONS[0] + 1;
            TimeStamp[0][1] = timestamp;
            log_value_A = !log_value_A;
        }
    }
    if(TimeStamp[0][1] > TimeStamp[0][0]){
        TimePeriod[0] = TimeStamp[0][1] - TimeStamp[0][0];
    }
    else TimePeriod[0] = 0;
}

void gpio_callback_channel_B(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_RISE) {
    
        uint64_t timestamp = time_us_64();
        
        if(log_value_B) {
            TimeStamp[1][0] = timestamp;
            log_value_B = !log_value_B;
        }
        else {
            TimeStamp[1][1] = timestamp;
            log_value_B = !log_value_B;
            REVOLUTIONS[1] += 1;
        }
    }
    if(TimeStamp[1][1] > TimeStamp[1][0]){
        TimePeriod[0] = TimeStamp[1][1] - TimeStamp[1][0];
    }
    else TimePeriod[1] = 0;
}

int main() {
    stdio_init_all();

    gpio_init(EDGE_GPIO_A);
    gpio_set_dir(EDGE_GPIO_A, GPIO_IN);
    gpio_pull_down(EDGE_GPIO_A);

    gpio_init(EDGE_GPIO_B);
    gpio_set_dir(EDGE_GPIO_B, GPIO_IN);
    gpio_pull_down(EDGE_GPIO_B);

    gpio_set_irq_enabled_with_callback(EDGE_GPIO_A, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel_A);
    gpio_set_irq_enabled_with_callback(EDGE_GPIO_B, GPIO_IRQ_EDGE_RISE, true, &gpio_callback_channel_B);

    uint8_t i = 0;

    while (1) {
        printf("TimePeriod A: %llu us\n", TimePeriod[0]);
        // printf("TimePeriod B: %llu us\n", TimePeriod[1]);
        if(i == 10){
            printf("TimePeriod A: %llu us ", TimePeriod[0]);
            printf("Revolutions A: %u\n", REVOLUTIONS[1]);
            // printf("Revolutions B: %u\n", Revolutions[1]);
            i = 0;
        } 
        i++;
        sleep_ms(100);
    }

    return 0;
}
