#include <tusb.h>
#include <stdarg.h>
// #include "EncoderData.h"


#define USB_BUFFER_SIZE 256

#define TUSB_MSG_START 0xFD
#define TUSB_MSG_STOP  0xFE
#define TUSB_MSG_RESEND 0x78

#define TUSB_MSG_ID_PING     0x50
#define TUSB_MSG_ERR_OVER_LEN 0x4F
#define TUSB_MSG_ERR_CHECKSUM 0x4E
#define TUSB_MSG_ERR_UNKNOWN  0x4D

#define TUSB_MSG_ID_ACTUATOR 0x61
#define TUSB_MSG_ID_ENCODER  0x65
#define TUSB_MSG_ID_MOTOR    0x6D
#define TUSB_MSG_ID_IMU      0x69

bool allocate_pwm = true;

uint8_t pwmValues[4] = {0, 0, 0, 0};
uint8_t actuatorValue = 0;

uint8_t resendMsg_OverLen[1] = {TUSB_MSG_ERR_OVER_LEN};
uint8_t resendMsg_Checksum[1] = {TUSB_MSG_ERR_CHECKSUM};
uint8_t resendMsg_Unknown[1] = {TUSB_MSG_ERR_UNKNOWN};

uint32_t sendUSBMessage(uint8_t msgID, uint8_t *data, uint8_t len);
uint32_t readUSBBuffer();

