#include <tusb.h>
#include <stdarg.h>
// #include "EncoderData.h"


#define USB_BUFFER_SIZE 64
#define MAX_PACKET_SIZE 32

#define TUSB_MSG_START 0xFD
#define TUSB_MSG_STOP  0xFE
#define TUSB_MSG_RESEND 0x78
#define TUSB_MSG_ID_LOG_STATEMENTS 0x4C

#define TUSB_MSG_ID_PING     0x50
#define TUSB_MSG_ERR_OVER_LEN 0x4F
#define TUSB_MSG_ERR_CHECKSUM 0x4E
#define TUSB_MSG_ERR_UNKNOWN  0x4D

#define TUSB_MSG_ID_ACTUATOR 0x61
#define TUSB_MSG_ID_ENCODER  0x65
#define TUSB_MSG_ID_MOTOR    0x6D
#define TUSB_MSG_ID_IMU      0x69

uint8_t pwmValues[4] = {0, 0, 0, 0};
uint8_t imuValue[4] = {0, 0, 0, 0};
uint8_t actuatorValue = 0;

uint8_t resendMsg_OverLen[1] = {TUSB_MSG_ERR_OVER_LEN};
uint8_t resendMsg_Checksum[1] = {TUSB_MSG_ERR_CHECKSUM};
uint8_t resendMsg_Unknown[1] = {TUSB_MSG_ERR_UNKNOWN};

uint32_t sendUSBMessage(uint8_t msgID, uint8_t *data, uint8_t len);
uint32_t readUSBBuffer();
uint32_t push_message(const char* format, ...);


uint32_t sendUSBMessage(uint8_t msgID, uint8_t *data, uint8_t len) {
    
    if(!tud_cdc_connected()) {
        push_message("USB not connected\n");
        return 0;
    }
    
    uint8_t msg[64];
    msg[0] = TUSB_MSG_START;
    msg[1] = msgID;
    for (int i = 0; i < len; i++) {
        msg[i + 2] = data[i];
    }

    uint8_t checksum = 0;
    checksum ^= msgID; 
    checksum ^= (uint8_t) len;
    for (int i = 0; i < len; i++) {
        checksum ^= data[i]; 
    }

    msg[len + 3] = checksum;
    msg[len + 4] = TUSB_MSG_STOP;
    return tud_cdc_write(msg, len + 3);
}

uint32_t readUSBBuffer(){

    if(!tud_cdc_connected()) {
        push_message("USB not connected\n");
        return 2;
    }

    // push_message("Reading USB Buffer\n");

    uint8_t buffer[USB_BUFFER_SIZE];
    uint8_t recLen = tud_cdc_available(); 

    if(recLen > USB_BUFFER_SIZE){
        sendUSBMessage(TUSB_MSG_RESEND, resendMsg_OverLen, 1);
        return 1;
    }

    if(recLen > 0){
        tud_cdc_read(buffer, recLen);
        
        uint8_t msgID = buffer[1];
        uint8_t len = buffer[2];
        uint8_t checksum = 0;
        
        checksum ^= msgID;
        checksum ^= len;
        for (int i = 0; i < len; i++) {
            checksum ^= buffer[i + 3];
        }
        
        if(checksum == buffer[recLen - 2]){
            push_message("\n Message received \n");
            switch (msgID) {
                
                case TUSB_MSG_ID_ACTUATOR:
                    push_message("\n Actuator ID aayi hai \n");
                    actuatorValue = buffer[3];
                    break;

                case TUSB_MSG_ID_MOTOR:
                    push_message("\n Motor ID aayi hai \n");
                    for(uint8_t i = 0; i < 4; i++){
                        pwmValues[i] = buffer[i + 3];
                    }
                    push_message("Motor values received\n");
                    break;
                
                default:
                    push_message("\n Unknown ID aayi hai \n");
                    sendUSBMessage(TUSB_MSG_RESEND, resendMsg_Unknown, 1);
                    break;
            }
        }
        else{
            sendUSBMessage(TUSB_MSG_ERR_CHECKSUM, resendMsg_Checksum, 1);
        }
        push_message("Message read\n");
    }
    return 0;

}

uint32_t push_message(const char* format, ...){
    
    char buffer[256] = {0};  // Large enough to hold most messages
    va_list args;
    va_start(args, format);
    int message_len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (message_len < 0) {
        return 1;  // Error formatting the string
    }

    if (message_len >= (int)sizeof(buffer)) {
        message_len = sizeof(buffer) - 1;  // Truncate if necessary
        buffer[message_len] = '\0';  // Ensure null termination
    }

    // tud_cdc_write_clear();

    message_len = strlen(buffer);
    size_t offset = 0;

    // while (offset < message_len) {
    //     size_t chunk_size = (message_len - offset > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : (message_len - offset);
    //     sendUSBMessage(TUSB_MSG_ID_LOG_STATEMENTS, (uint8_t *)buffer + offset, chunk_size);
    //     offset += chunk_size;
    // }
    if (tud_cdc_write_available() >= message_len) {
        tud_cdc_write(buffer, message_len);
        tud_cdc_write_flush();
    }

    tud_task(); // Poll the USB stack to send the message

    return 0;
}
