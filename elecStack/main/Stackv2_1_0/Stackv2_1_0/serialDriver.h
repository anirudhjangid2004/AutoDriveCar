#include <stdarg.h>
// #include "EncoderData.h"


#define BUFFER_SIZE 64
#define MAX_PACKET_SIZE 32

#define MSG_START 0xFD
#define MSG_STOP  0xFE
#define MSG_RESEND 0x78
#define MSG_ID_LOG_STATEMENTS 0x4C

#define MSG_ID_PING      0x50
#define MSG_ERR_OVER_LEN 0x4F
#define MSG_ERR_CHECKSUM 0x4E
#define MSG_ERR_UNKNOWN  0x4D

#define MSG_ID_ACTUATOR (uint8_t)0x61
#define MSG_ID_ENCODER  (uint8_t)0x65
#define MSG_ID_MOTOR    (uint8_t)0x6D
#define MSG_ID_IMU      (uint8_t)0x69

uint8_t pwmValues[4] = {0, 0, 0, 0};
uint8_t imuValue[4] = {0, 0, 0, 0};
uint8_t actuatorValue = 0;


uint32_t sendMessage(uint8_t msgID, uint8_t *data, uint8_t len);
uint32_t readBuffer();


/*
    Function to send data over serial bytewise
    @param msgID: Message ID
    @param data: Data to be sent
    @param len: Length of data
    @return: 0
*/
