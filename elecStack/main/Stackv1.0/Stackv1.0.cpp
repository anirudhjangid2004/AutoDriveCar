#include "Stackv1.0.h"

int main()
{
    RMCS2303 motorController;
    motorController.Serial0(BAUDRATE);

    stdio_init_all();
    
    while (true)
    {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
