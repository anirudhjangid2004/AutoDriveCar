## Communication Protocol

### Data to be shared

From Pico to Jetson
- IMU data
- Encoder Revolutions

From Jetson to Pico
- Speed values for all the motors
- Actuator commands

### Communication Data
Motors

- PWM value to be sent for all 4 of them simultaneously. Range of PWM values will be between 0 to 100.

Actuator

- Only 1 bit, to raise or pull the actuator down.

