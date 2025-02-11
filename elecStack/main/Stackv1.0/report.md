### General flow of Elec Stack

#### Pin Planning

- 2 sets of UART
- 4 Toggle controlled ports for 12V for motors
- 2 Toggle controlled ports for 5V 1 for SBC, redundant
- I2C for IMU
- 2 Interrupt pins
- 1 Toggle for fork
- 1 ADC pin for reading battery voltage
- Toggle port for battery monitoring


#### Description

- "UART 1" to send data to motor drivers in terms of its speed
- "UART 2" for replacement or expansion
- Motor toggle ports to cut power off to them in case of low battery
