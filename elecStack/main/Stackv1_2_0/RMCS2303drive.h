#ifndef RMCS2303drive_h
#define RMCS2303drive_h

#include <pico/stdlib.h>
#include <pico/time.h>
#include <pico/binary_info.h>
#include <pico/stdio/driver.h>
#include <pico/stdio.h>
#include <stdio.h>
#include <string>
using std::string;
// #include "SoftwareSerial.h"
// #include "Arduino.h"

#define UARTID uart0
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1

typedef unsigned char byte;
typedef unsigned int word;

class RMCS2303
{
  // user-accessible "public" interface
  public:
    void Serial0(long baudrate);
    void Serial_selection(byte x);
    // void begin(HardwareSerial *hport,long baudrate);
    // void begin(SoftwareSerial *sport, long baudrate);
    byte Enable_Digital_Mode(byte slave_id,byte dir);
    byte Speed(byte slave_id,int SPEED);    
    byte EncoderPosition_LPR(byte slave_id,int LPR);
    byte EncoderPosition_CPR(byte slave_id,unsigned long int CPR);
    byte Acceleration(byte slave_id,int acceleration);
    byte ProportionalGain(byte slave_id,int PP_GAIN);
    byte IntegralGain(byte slave_id,int PI_GAIN);
    byte FeedforwardGain(byte slave_id,int VF_GAIN);
    byte Absolute_move(byte slave_id, long int count);
    byte WriteSingleRegister(byte slave_id, int address, unsigned int value);
    byte EncoderPosition_enable(byte slave_id);
    byte Disable_Position_Mode(byte slave_id);
    byte Absolute_position(byte slave_id,long int count);
    string ReadSingleRegister(byte slave_id, int address,unsigned int No_register);
    string Modbus_string(byte slave_id,byte FC,int address,unsigned int data);
    string print_hex(byte number);
    byte nibble(char c);
    byte LRC(string s,byte len);
    void hexToBytes(byte *byteArray, char *hexString);
    long int Speed_Feedback(byte slave_id) ;
    long int Position_Feedback(byte slave_id);
    long int value(string input);
    byte READ_PARAMETER(byte slave_id);
    long int READ_DEVICE_MODBUS_ADDRESS(byte slave_id);
    long int READ_INP_CONTROL_BYTE(byte slave_id);
    long int READ_INP_MODE_BYTE (byte slave_id);
    long int READ_PP_GAIN_BYTE(byte slave_id);
    long int READ_PI_GAIN_BYTE(byte slave_id);
    long int READ_VF_GAIN_BYTE (byte slave_id);
    long int READ_LINES_PER_ROT(byte slave_id);
    long int READ_TRP_ACL_WORD (byte slave_id);
    byte WRITE_PARAMETER(byte slave_id,int INP_CONTROL_MODE,int PP_gain,int PI_gain,int VF_gain,int LPR,int acceleration,int Speed);
    long int READ_TRP_SPD_WORD(byte slave_id);
    byte SAVE(byte slave_id);
    byte RESET(byte slave_id);
    byte Disable_Digital_Mode(byte slave_id,byte dir);
    byte Brake_Motor(byte slave_id,byte dir);
    byte ESTOP(byte slave_id);
    byte STOP(byte slave_id);
    byte SET_HOME(byte slave_id);
    byte Restart(byte slave_id);
    byte Enable_Analog_Mode(byte slave_id);
    byte Disable_Analog_Mode(byte slave_id);
  private:

};
#endif
