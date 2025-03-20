#include "usbDriver.h"

uint32_t sendUSBMessage(uint8_t msgID, uint8_t *data, uint8_t len) {
    
    if(!tud_cdc_connected()) {
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
        return 2;
    }

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
            switch (msgID) {
                
                case TUSB_MSG_ID_ACTUATOR:
                    actuatorValue = buffer[3];
                    break;

                case TUSB_MSG_ID_MOTOR:
                    for(uint8_t i = 0; i < 4; i++){
                        pwmValues[i] = buffer[i + 3];
                    }
                    break;
                
                default:
                    sendUSBMessage(TUSB_MSG_RESEND, resendMsg_Unknown, 1);
                    break;
            }
        }
        else{
            sendUSBMessage(TUSB_MSG_ERR_CHECKSUM, resendMsg_Checksum, 1);
        }
    }
    return 0;

}