# !/bin/bash
cd /home/$USER/pico/pico-examples/build/BNO055

cmake .
make
cp BNO055_imu.uf2 /media/$USER/RPI-RP2/