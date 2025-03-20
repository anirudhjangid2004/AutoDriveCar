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

IMU

- Accelerations in all three directions.
- Angular velocity for all 3 axes.

Encoder

- Only sending the revolutions will help.

### Communication Protocol

    Start character 0xFD
    Stop Character  0xFE

    Packet Format : <START><ID><DATA><CRC><STOP> 

Motors

    ID   : "m" or 0x6D
    DATA : 4 consecuticve PWM values ranging from 0x00 to 0x64, mapped to respective motors

Actuator

    ID   : "a" or 0x61
    DATA : 0x00 or 0x01, depending on extending or contracting the actuator.
    
IMU 

    ID   : 0x69 or "i"
    DATA : All 3 accelerations in x y z order followed by angular velocity along 3 axes x y z in that order.

Encoder Revolutions

    ID   : "e" or 0x65
    DATA : Revolutions of all motors 1 2 3 4 in that order

Retransmit Data

    ID   : "x" or 0x78


