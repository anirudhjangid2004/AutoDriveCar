#ifndef USBDRIVER_H
#define USBDRIVER_H

#include <tusb.h>
#include <stdarg.h>
#include "motorDriver.h"
#include "pinPlan.h"
// #include "EncoderData.h"

extern bool kill_me;

#define USB_BUFFER_SIZE 64
#define MAX_PACKET_SIZE 32

#define TUSB_MSG_START (uint8_t)0xFA
#define TUSB_MSG_STOP  (uint8_t)0xFB
#define TUSB_MSG_RESEND 0x78
#define TUSB_MSG_ID_LOG_STATEMENTS 0x4C

#define TUSB_MSG_ID_PING      0x50
#define TUSB_MSG_ERR_OVER_LEN 0x4F
#define TUSB_MSG_ERR_CHECKSUM 0x4E
#define TUSB_MSG_ERR_UNKNOWN  0x4D

#define TUSB_MSG_ID_ACTUATOR (uint8_t)0x61
#define TUSB_MSG_ID_ENCODER  (uint8_t)0x65
#define TUSB_MSG_ID_MOTOR    (uint8_t)0x6D
#define TUSB_MSG_ID_IMU      (uint8_t)0x69
#define TUSB_MSG_ID_ODO_DATA (uint8_t)0x72
#define TUSB_MSG_ID_KILL     (uint8_t)0x77
#define TUSB_MSG_ID_MTR_DIRN (uint8_t)0x70

bool skip_checksum = true;

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
    msg[2] = len;
    for (int i = 0; i < len; i++) {
        msg[i + 3] = data[i];
    }

    uint8_t checksum = 0;
    checksum ^= msgID; 
    checksum ^= (uint8_t) len;
    for (int i = 0; i < len; i++) {
        checksum ^= data[i]; 
    }

    msg[len + 3] = checksum;
    msg[len + 4] = TUSB_MSG_STOP;
    uint32_t ret = tud_cdc_write(msg, len + 4);
    tud_cdc_write_flush();

    tud_task(); // Poll the USB stack to send the message
    sleep_ms(2);
    return ret;
}

/*
    Function to read the USB buffer
    Reads the USB buffer and processes the message
*/
uint32_t readUSBBuffer(){

    if(!tud_cdc_connected()) {
        push_message("USB not connected\n");
        return 2;
    }

    uint8_t buffer[USB_BUFFER_SIZE] = {0};
    uint8_t recLen = tud_cdc_available(); 

    if(recLen > USB_BUFFER_SIZE){
        push_message("Over length message received\n");
        return 1;
    }

    if(recLen > 0){
        uint32_t count = tud_cdc_read(buffer, recLen);
        
        // Read the received message
        printf("Received HEX: ");
        for (uint32_t i = 0; i < count; i++) {
            printf("%02X ", buffer[i]);
        }
        printf("\n");

        // Find the start byte
        uint8_t start = 0;

        if(buffer[start] == TUSB_MSG_START){
            push_message("First index is start\n");
        }

        while (start < recLen && buffer[start] != TUSB_MSG_START) {
            push_message("Start byte not found\n");
            start++;
        }

        if(start == recLen){
            push_message("No start byte found finally\n");
            return 1;
        }

        uint8_t msgID = buffer[start + 1];
        uint8_t len = buffer[start + 2];
        uint8_t checksum = 0;

        // Verify the checksum
        checksum ^= msgID;
        checksum ^= len;
        for (int i = 0; i < len; i++) {
            checksum ^= buffer[i + 3 + start];
        }
        
        if(checksum == buffer[recLen - 2 + start] || skip_checksum){

            switch (msgID) {
                
                case TUSB_MSG_ID_ACTUATOR:
                    push_message("\n Actuator values received\n");
                    actuatorValue = buffer[3];
                    break;

                case TUSB_MSG_ID_MOTOR:
                    push_message("Motor values received\n");
                    for(uint8_t i = 0; i < 4; i++){
                        pwmValues[i] = buffer[i + 3];
                    }
            //         set_pwm(PWM_PIN_1, buffer[3]);
            //         set_pwm(PWM_PIN_2, buffer[4]);
            //         set_pwm(PWM_PIN_3, buffer[5]);
            // s       set_pwm(PWM_PIN_4, buffer[6]);
                    push_message("Motor values set\n");
                    sleep_ms(4);
                    for(uint8_t i = 0; i < 4; i++){
                        printf("Motor %d: %d\n", i, pwmValues[i]);
                    }
                    break;

                case TUSB_MSG_ID_KILL:
                    push_message("Kill message received\n");
                    kill_me = true;
                    break;

                case TUSB_MSG_ID_MTR_DIRN:
                    push_message("Motor direction message received\n");
                    for(uint8_t i = 0; i < 4; i++){
                        if(buffer[i + 3] == 1) dirn[i] = true;
                        else dirn[i] = false;
                    }

                    set_motor_dirn();
                    push_message("Motor direction values set\n");
                    sleep_ms(4);
                    break;
                
                default:
                    push_message("\n Unknown ID received \n");
                    break;
            }
        }
        else{
            push_message("Checksum error\n");
        }
        sleep_ms(2);
        push_message("Message read\n");
    }
    // To clear the buffer off
    tud_cdc_write_clear();
    // push_message("Buffer cleared\n");
    sleep_ms(4);
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

    if (tud_cdc_write_available() >= message_len) {
        tud_cdc_write(buffer, message_len);
        tud_cdc_write_flush();
    }

    tud_task(); // Poll the USB stack to send the message

    return 0;
}

#endif