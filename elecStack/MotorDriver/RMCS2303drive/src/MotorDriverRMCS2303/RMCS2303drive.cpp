#include "RMCS2303drive.h"
#include <string.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
using std::string;
// #include "SoftwareSerial.h"
// #include "Arduino.h"

/*
    Considering Serial as uart
*/

byte Sprt;

// HardwareSerial *port;
// SoftwareSerial *softport;

const byte MaxByteArraySize = 8;
byte byteArray[MaxByteArraySize] = {0};

// This sets the baud rate for the serial
void RMCS2303::Serial0(long baudrate)
    {
        uart_init(UARTID, baudrate);
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
        uart_set_hw_flow(UARTID, false, false);
        uart_set_format(UARTID, DATA_BITS, STOP_BITS, PARITY);
        // Serial.begin(baudrate);
    }
	
// This function is used to select the serial port
// Used to select between hardware or software serial port
// We will anyways go ahead with the hardware serial port
// void RMCS2303::Serial_selection(byte x)
//     {   
//         if(x==0)  Sprt=0;
//         if(x==1)  Sprt=1;
//     }
     
// Binding the hardware serial port with Serial     
// void RMCS2303::begin(HardwareSerial *hport,long baudrate)
//     {
//         port=hport;
//         if(port==&Serial)
//         {
//             Serial.println("error");
//             Serial.println("Use other serial port");
//             Serial.end();
//         }
//         else
//             port->begin(baudrate);
//     }

// Binding the software serial port with softport
// void RMCS2303::begin(SoftwareSerial *sport,long baudrate)
//     {
//         softport=sport;
//         softport->begin(baudrate);
//     }
	
// We wont be using the analog mode    
byte RMCS2303::Enable_Analog_Mode(byte slave_id)
{
    byte j;
        j=WriteSingleRegister(slave_id,2,1);
        if(j==1) return 1;
        else return 0;
}

// Analog mode can
byte RMCS2303::Disable_Analog_Mode(byte slave_id)
{
    byte j;
        j=WriteSingleRegister(slave_id,2,0);
        if(j==1) return 1;
        else return 0;
}	
	
// Digital Mode will be used
byte RMCS2303::Enable_Digital_Mode(byte slave_id, byte dir)
    {
        int data; byte j;
        if(dir==0)   data=257;
        if(dir==1)   data=265;
        j=WriteSingleRegister(slave_id,2,data);
        if(j==1) return 1;
        else return 0;
    }
	
byte RMCS2303::Disable_Digital_Mode(byte slave_id,byte dir)
    { 
        int data; byte j,slave_id;
        if(dir==0)   data=256;
        if(dir==1)   data=264;
        j=WriteSingleRegister(slave_id,2,data);
        if(j==1) return 1;
        else return 0;
    }
	
byte RMCS2303::Absolute_position(byte slave_id,long int count)
    {  
        byte j,k;
        j=Absolute_move(slave_id,count);
        if(j==1)
        k=EncoderPosition_enable(slave_id);
     
        if(k==1) return 1;
        else return 0;
      
    }
	
byte RMCS2303::Speed(byte slave_id, int SPEED)
    {  
        byte j;
    
        j=WriteSingleRegister(slave_id,14,SPEED);
        if(j==1) return 1;
        else return 0;
    }
   	
long int RMCS2303::Speed_Feedback(byte slave_id) 
    {     
        string result,result1,out,x,y;  int w;char a[9];char *endptr;unsigned long int q;long int p;
        result1=ReadSingleRegister( slave_id,24,1);
        q = value( result1);
        if(q>32765) p=q-65535;
        else p=q;
        return (p);
    }
	
byte RMCS2303::Brake_Motor(byte slave_id,byte dir)
    { 
        int data; byte j;
        if(dir==0)   data=260;
        if(dir==1)   data=268;
        j=WriteSingleRegister(slave_id,2,data);
        if(j==1) return 1;
        else return 0;
    }

byte RMCS2303::EncoderPosition_LPR(byte slave_id,int LPR)
    {
        byte j;
        j=WriteSingleRegister(slave_id, 10, LPR);
        if(j==1) return 1;
        else return 0;
    }
	
byte RMCS2303::Disable_Position_Mode(byte slave_id)
    {
        byte j;
        j=WriteSingleRegister(slave_id,2,512);
        if(j==1) return 1;
        else return 0;
    }
    
byte RMCS2303::EncoderPosition_enable(byte slave_id)
    {   
        byte j;
        j=WriteSingleRegister(slave_id,2,513);
       
        if(j==1) return 1;
        else return 0;
    }	
     
byte RMCS2303::Absolute_move(byte slave_id, long int count)
    { 
        unsigned long int data;
        byte j,k;
        if(count>=0 && count<2147483647)          data=count;
        if(count<0 && count>=-2147483648)        data = 4294967295 - (count * -1);
        unsigned int Hidata = data >> 16;
        unsigned int Lodata = data & 0xFFFF;
        j=WriteSingleRegister(slave_id,16,Lodata);
        if(j==1)
        {k=WriteSingleRegister(slave_id,18,Hidata);}
     
        if(k==1) return 1;
        else return 0;
    }

byte RMCS2303::Acceleration(byte slave_id,int acceleration)
    {
        byte j;
        j= WriteSingleRegister(slave_id, 12, acceleration);
        if(j==1) return 1;
        else return 0;
    }

byte RMCS2303::ProportionalGain(byte slave_id,int PP_GAIN)
    {
        byte j;
        j=WriteSingleRegister(slave_id, 4, PP_GAIN);
        if(j==1) return 1;
        else return 0;
    }

byte RMCS2303::IntegralGain(byte slave_id,int PI_GAIN)
    {
        byte j;
        j=WriteSingleRegister(slave_id, 6,PI_GAIN );
        if(j==1) return 1;
        else return 0;
    }

byte RMCS2303::FeedforwardGain(byte slave_id,int VF_GAIN)
    {
        byte j;
        j=WriteSingleRegister(slave_id, 8, VF_GAIN);
        if(j==1) return 1;
        else return 0;
    }
	
long int RMCS2303::Position_Feedback(byte slave_id) 
    {     
        string result,result1,out,x,y;  int w;char a[9];char *endptr;unsigned long int q;long int p;
        result1=ReadSingleRegister( slave_id,20,2);
        x=result1.substr(7,8);  // Adjusted
        
        strncpy(a, x.c_str(), sizeof(a) - 1);
        a[sizeof(a) - 1] = '\0';
        // x.toCharArray(a,9);
        for(int i=0;i<4;i++)
        {
            char c=a[i];
            a[i]=a[i+4];
            a[i+4]=c; 
        }
        q=strtoul(a,&endptr, 16);
        if(q>2147483647) p=q-4294967295;
        else p=q;
        return(p);
    }	
  
// Most important function
byte RMCS2303::WriteSingleRegister(byte slave_id, int address,unsigned int value)
    {   
        string response,res;
        byte j;
        string result=Modbus_string(slave_id,6,address,value);
        uart_puts(UARTID, result.c_str());
        // port->print(result);
        sleep_ms(50);                      // Instead of delay
        
        while (uart_is_readable(UARTID))
        {
            char buffer[256];
            int index = 0;

            // Inner loop: Read a single line of data
            while (uart_is_readable_within_us(UARTID, 1000000) && index < 255)
            {
                buffer[index++] = uart_getc(UARTID);
                if (buffer[index - 1] == '\n')
                {
                    buffer[index] = '\0';
                    break;
                }
            }

            // Convert buffer to string
            response = string(buffer);
        }

        if(response[0] == '\0'){
            uart_puts(UARTID,"CHECK YOUR SLAVE_ID");
            // Serial.println("CHECK YOUR SLAVE_ID"); 
            return 0;
        }
        res=(response.substr(1,15));       // Adjusted
        j=LRC(res,6);
        if(j==1) return 1;
        else return 0;
        
        
        // if(Sprt==1) 
        // {
        //     softport->print(result);
            
        //     sleep_ms(50);
        //     while(softport->available())
        //     {response=softport->readStringUntil('\n');}
        //     if(response[0] == '\0')
        //     {
        //         uart_puts(UARTID,"CHECK YOUR SLAVE_ID");
        //         // Serial.println("CHECK YOUR SLAVE_ID");
        //         return 0;
        //         }
        //     res=(response.substr(1,15));      // Adjusted
        //     j=LRC(res,6);
          
        //     if(j==1) return 1;
        //     else return 0;
        // }
        
    }
    
string RMCS2303::Modbus_string(byte slave_id, byte FC, int address, unsigned int data)
    {
        byte sum =0;
        byte AddLoByte,AddHiByte,dataLoByte,dataHiByte;
        AddLoByte=AddHiByte=dataLoByte=dataHiByte=0;
        AddLoByte = (address & 0x00FF);
        AddHiByte = ((address & 0xFF00) >>8);
        dataLoByte = (data & 0x00FF);
        dataHiByte = ((data & 0xFF00) >>8);
        sum = 0;
        sum -= slave_id;
        sum -= FC;
        sum -= AddLoByte;
        sum -= AddHiByte;
        sum -= dataLoByte;
        sum -= dataHiByte;

        string SLAVE  = print_hex(slave_id);
        string FCN    = print_hex(FC);
        string AddHi  = print_hex(AddHiByte);
        string AddLo  = print_hex(AddLoByte);
        string dataHi = print_hex(dataHiByte);
        string dataLo = print_hex(dataLoByte);
        string LRC    = print_hex(sum);
        string result =":"+ SLAVE+FCN+AddHi+AddLo+dataHi+dataLo+LRC+"\r\n";

        return result;
    }

string RMCS2303::print_hex(byte number)
    {
        // string value = string(number,HEX);
        // std::transform(value.begin(), value.end(), value.begin(), ::toupper);
        // // value.toUpperCase();
        // if(value.length()==1){value = "0" + value;}
        // return(value);
        std::stringstream ss;
        ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(number);
        return ss.str();
    }

string RMCS2303::ReadSingleRegister(byte slave_id, int address,unsigned int No_register) 
    {   
        string response,res; byte j;
        string result = Modbus_string(slave_id,3,address,No_register);
        // if(Sprt==0)
        // { 
        uart_puts(UARTID, result.c_str());
        // port->print(result);
        sleep_ms(20);
        
        while (uart_is_readable(UARTID))
        {
            char buffer[256];
            int index = 0;

            // Inner loop: Read a single line of data
            while (uart_is_readable_within_us(UARTID, 1000000) && index < 255)
            {
                buffer[index++] = uart_getc(UARTID);
                if (buffer[index - 1] == '\n')
                {
                    buffer[index] = '\0';
                    break;
                }
            }
            // Convert buffer to string
            response = string(buffer);
        }   
        
        res=response.substr(1,17);      // Adjusted
        j=LRC(res,7);
        
        if(j==1) return(response);
        else return "0";

        // }

        // if(Sprt==1)
        // {
        //     softport->print(result);
        //     sleep_ms(20);
        //     while(softport->available())
        //     {    
        //         response=(softport->readstringUntil('\n'));
        //         uart_puts(UARTID,"<<");
        //         // Serial.print("<<");
        //     }
        //     res=response.substr(1,17);      // Adjusted
        //     j=LRC(res,7);
        //     if(j==1) return(response);
        //     else return "0";
        // }
    }
    
byte RMCS2303:: WRITE_PARAMETER(byte slave_id,int INP_CONTROL_MODE,int PP_GAIN,int PI_GAIN,int VF_GAIN,int LPR,int acceleration,int SPEED)
{   byte W1,W2,W3,W4,W5,W6,W7,W8;
    W1=W2=W3=W4=W5=W6=W7=W8=0;
    W1=WriteSingleRegister(slave_id,2,INP_CONTROL_MODE);
    if(W1==1) {
        // Serial.println("INP_CONTROL :          DONE");
        uart_puts(UARTID,"INP_CONTROL :          DONE");
        // Serial.println("INP_MODE :             DONE");
        uart_puts(UARTID,"INP_MODE :             DONE");
        }
    else {
        // Serial.print("error in writing parameters"); 
        uart_puts(UARTID,"error in writing parameters");
        // Serial.end();
        uart_deinit(UARTID);
        } 
    
    W3=ProportionalGain( slave_id, PP_GAIN); 
    if(W3==1) uart_puts(UARTID, "PP_GAIN :              DONE"); //Serial.println("PP_GAIN :              DONE");
    else {
        // Serial.print("error in writing parameters"); 
        uart_puts(UARTID,"error in writing parameters");
        uart_deinit(UARTID);
        // Serial.end();
        } 
    
    W4=IntegralGain( slave_id, PI_GAIN);
    if(W4==1) 
        uart_puts(UARTID,"PI_GAIN :              DONE");
        // Serial.println("PI_GAIN :              DONE");
    else {
        // Serial.print("error in writing parameters"); 
        uart_puts(UARTID,"error in writing parameters");
        uart_deinit(UARTID);
        // Serial.end();
        } 
    
    W5=FeedforwardGain( slave_id, VF_GAIN);
    if(W5==1) 
        uart_puts(UARTID,"VF_GAIN :              DONE");
        // Serial.println("VF_GAIN :              DONE");
    else {
        // Serial.print("error in writing parameters");
        uart_puts(UARTID,"error in writing parameters");
        uart_deinit(UARTID);
        // Serial.end();
        } 
    
    W6=EncoderPosition_LPR( slave_id, LPR);
    if(W6==1) 
        uart_puts(UARTID,"LPR :                  DONE");    
        // Serial.println("LPR :                  DONE");
    else {
        uart_puts(UARTID,"error in writing parameters");
        uart_deinit(UARTID);
        // Serial.print("error in writing parameters"); 
        // Serial.end();
        } 
    
    
    W7=Acceleration( slave_id, acceleration);
    if(W7==1) 
        uart_puts(UARTID,"ACCELERATION :         DONE");
        // Serial.println("ACCELERATION :         DONE");
    else {
        uart_puts(UARTID,"error in writing parameters");
        uart_deinit(UARTID); 
        // Serial.print("error in writing parameters"); 
        // Serial.end();
        } 
    
    W8=Speed( slave_id,SPEED);
     if(W8==1) 
        uart_puts(UARTID,"SPEED :                DONE");    
        // Serial.println("SPEED :                DONE");
    else {
        uart_puts(UARTID,"error in writing parameters");
        uart_deinit(UARTID);
        // Serial.print("error in writing parameters"); 
        // Serial.end();
        }
    
    if(W1 & W2 & W3 & W4 & W5 & W6 & W7 & W8==1)
    {
		byte c;
		c=SAVE(slave_id);
		if(c==1) {
            uart_puts(UARTID,"ALL PERAMETER SET");
            uart_puts(UARTID,"\n");
            // Serial.println("ALL PERAMETER SET"); 
            // Serial.print("\n");
        }
		else 
            uart_puts(UARTID,"NOT SAVED");
            // Serial.print("NOT SAVED");
    }
}

byte RMCS2303::READ_PARAMETER(byte slave_id)
{  
	long int R1,R2,R3,R4,R5,R6,R7,R8,R9;
    R1=R2=R3=R4=R5=R6=R7=R8=R9=0;
    
    char buffer[50];

	R1=READ_DEVICE_MODBUS_ADDRESS(slave_id);
    if(R1>=0)
    {
        uart_puts(UARTID,"DEVICE_MODBUS_ADDRESS: ");
        sprintf(buffer, "%ld", R1);
        uart_puts(UARTID,buffer);
        // Serial.print("DEVICE_MODBUS_ADDRESS: ");
        // Serial.println(R1);
    }
    else 
    {   
        uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
        // Serial.end();
    }
    
    R2=READ_INP_CONTROL_BYTE(slave_id);
    if(R2>=0)
    {
		uart_puts(UARTID,"INP_CONTROL_BYTE: ");
        sprintf(buffer, "%ld", R2);
        uart_puts(UARTID,buffer);
        // Serial.print("INP_CONTROL_BYTE: ");
		// Serial.println(R2);
	}
    else 
    {	
        uart_puts(UARTID,"ERROR IN READING");
        sprintf(buffer, "%ld", R2);
        uart_puts(UARTID,buffer);
        uart_deinit(UARTID);
        // Serial.println(R2);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
    
    R3=READ_INP_MODE_BYTE(slave_id);
    if(R3>=0)
    {
		uart_puts(UARTID,"INP_MODE_BYTE: ");
        sprintf(buffer, "%ld", R3);
        uart_puts(UARTID,buffer);
        // Serial.print("INP_MODE_BYTE: ");
		// Serial.println(R3);
	}
    else 
    {
		uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
    
    R4=READ_PP_GAIN_BYTE(slave_id);
    if(R4>=0)
    {
		uart_puts(UARTID,"PP_GAIN_BYTE: ");
        sprintf(buffer, "%ld", R4);
        uart_puts(UARTID,buffer);
        // Serial.print("PP_GAIN_BYTE: ");
		// Serial.println(R4);
	}
    else 
    {
		uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
    
    R5=READ_PI_GAIN_BYTE(slave_id);
    if(R5>=0)
    {
		uart_puts(UARTID,"VI_GAIN_BYTE: ");
        sprintf(buffer, "%ld", R5); 
        uart_puts(UARTID,buffer); 
        // Serial.print("VI_GAIN_BYTE: ");
		// Serial.println(R5);
	}
    else 
    {
		uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
    
    R6=READ_VF_GAIN_BYTE(slave_id);
    if(R6>=0)
    {
		uart_puts(UARTID,"VF_GAIN_BYTE: ");
        sprintf(buffer, "%ld", R6);
        uart_puts(UARTID,buffer);
        // Serial.print("VF_GAIN_BYTE: ");
		// Serial.println(R6);
	}
    else 
    {
		uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}

    R7=READ_LINES_PER_ROT(slave_id);
    if(R7>=0)
    {
        uart_puts(UARTID,"LINES_PER_ROT: ");
        sprintf(buffer, "%ld", R7);
        uart_puts(UARTID,buffer);
        // Serial.print("LINES_PER_ROT: ");
		// Serial.println(R7);
	}
    else 
    {	
        uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
    
    R8=READ_TRP_ACL_WORD(slave_id);
    if(R8>=0)
    {
		uart_puts(UARTID,"TRP_ACL_WORD: ");
        sprintf(buffer, "%ld", R8);
        uart_puts(UARTID, buffer);
        // Serial.print("TRP_ACL_WORD: ");
		// Serial.println(R8);
	}
    else 
    {
		uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
    
    R9=READ_TRP_SPD_WORD(slave_id);
    if(R9>=0)
    {
		uart_puts(UARTID,"TRP_SPD_WORD: ");
        sprintf(buffer, "%ld", R9);
        uart_puts(UARTID, buffer);
        // Serial.print("TRP_SPD_WORD: ");
		// Serial.println(R9);
	}
    else 
    {
		uart_puts(UARTID,"ERROR IN READING");
        uart_deinit(UARTID);
        // Serial.print("ERROR IN READING"); 
		// Serial.end();
	}
}


long int RMCS2303::READ_DEVICE_MODBUS_ADDRESS(byte slave_id) 
    {     
        string result,x; unsigned long int p;char a[9];int len;char *endptr;
        result=ReadSingleRegister( slave_id,1,1);
        x=result.substr(9,2);         // Adjusted
        
        strncpy(a, x.c_str(), sizeof(a) - 1);
        a[sizeof(a) - 1] = '\0';
        // x.toCharArray(a,3);
        p=strtoul(a,&endptr,16);
      return(p);
    }
long int RMCS2303::READ_INP_CONTROL_BYTE(byte slave_id) 
    {     
         string result,x; unsigned long int p;char a[9];int len;char *endptr;
        result=ReadSingleRegister( slave_id,2,1);
        x=result.substr(9,2);        // Adjusted
        
        strncpy(a, x.c_str(), sizeof(a) - 1);
        a[sizeof(a) - 1] = '\0';
        // x.toCharArray(a,3);
        p=strtoul(a,&endptr,16);
      return(p);
    }
long int RMCS2303::READ_INP_MODE_BYTE (byte slave_id) 
    {     
        string result,x; unsigned long int p;char a[9];int len;char *endptr;
        result=ReadSingleRegister( slave_id,3,1);
        x=result.substr(9,2);       // Adjusted
 
        strncpy(a, x.c_str(), sizeof(a) - 1);
        a[sizeof(a) - 1] = '\0';
        // x.toCharArray(a,3);
        p=strtoul(a,&endptr,16);
      return(p);
    }
long int RMCS2303::READ_PP_GAIN_BYTE(byte slave_id) 
    {     
        string result; unsigned long int q;
        result=ReadSingleRegister( slave_id,4,1);
        q = value( result);
        
      return(q);
    }
long int RMCS2303::READ_PI_GAIN_BYTE(byte slave_id) 
    {     
        string result; unsigned long int q;
        result=ReadSingleRegister( slave_id,6,1);
        q = value( result);
        
        return(q);
    }
long int RMCS2303::READ_VF_GAIN_BYTE (byte slave_id) 
    {     
        string result; unsigned long int q;
        result=ReadSingleRegister( slave_id,8,1);
        q = value( result);
      return(q);
    }


long int RMCS2303::READ_LINES_PER_ROT(byte slave_id) 
    {     
        string result; unsigned long int q;
        result=ReadSingleRegister( slave_id,10,1);
        q = value( result);
      return(q);
    }
long int RMCS2303::READ_TRP_ACL_WORD (byte slave_id) 
    {     
        string result; unsigned long int q;
        result=ReadSingleRegister( slave_id,12,1);
        q = value( result);
      return(q);
    }
long int RMCS2303::READ_TRP_SPD_WORD(byte slave_id)
{
    string result; unsigned long int q;
        result=ReadSingleRegister( slave_id,14,1);
        q = value( result);
       
      return(q);
}

byte RMCS2303::SAVE(byte slave_id)
{
     byte j;
        int save=((slave_id<<8)|0xFF);
        j=WriteSingleRegister(slave_id,0,save);
        if(j==1) return 1;
        else return 0;
}
byte RMCS2303::RESET(byte slave_id)
{
    byte j,k;
		j=WriteSingleRegister(slave_id,4,0);
		if(j==1) 
			k=SAVE(slave_id);
		if(k==1) return 1;
		else return 0;
}
byte RMCS2303::ESTOP(byte slave_id)
{
     byte j;
        j=WriteSingleRegister(slave_id,2,1792);
        if(j==1) return 1;
        else return 0;
}
byte RMCS2303::STOP(byte slave_id)
{
     byte j;
        j=WriteSingleRegister(slave_id,2,1793);
        if(j==1) return 1;
        else return 0;
}
byte RMCS2303::SET_HOME(byte slave_id)
{
     byte j;
        j=WriteSingleRegister(slave_id,2,2048);
        if(j==1) return 1;
        else return 0;
}
byte RMCS2303::Restart(byte slave_id)
{
     byte j;
        j=WriteSingleRegister(slave_id,2,2304);
        if(j==1) return 1;
        else return 0;
}
void RMCS2303::hexToBytes(byte *byteArray, char *hexString)
{
        byte currentByte = 0;  
        byte byteIndex = 0;

        for (byte charIndex = 0; charIndex < strlen(hexString); charIndex++)
        {
            bool oddCharIndex = charIndex & 1;
            if (!oddCharIndex)      // If the length is even
            {
            currentByte = nibble(hexString[charIndex]) << 4;  // Odd characters go into the high nibble
            }
            else
            {
            currentByte |= nibble(hexString[charIndex]);   // Odd characters go into low nibble
            byteArray[byteIndex++] = currentByte;
            currentByte = 0;
            }
        }
}

byte RMCS2303::nibble(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';

  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  return 0;  // Not a valid hexadecimal character
}

byte RMCS2303::LRC(string s,byte len)
{
        const char * const_ary = s.c_str();
        char* ary = new char[strlen(const_ary) + 1];
        strcpy(ary, const_ary);

        byte byteArray[MaxByteArraySize] = {0};
        hexToBytes(byteArray, ary);
        byte sum;
        sum=0;
        for(int i=0;i<len;i++)
        {
            sum+=byteArray[i];
        }
        byte LRC=(~sum)+1;
        
        delete[] ary;      // Free up the allocated memory

		if(LRC==byteArray[len])  return 1;
        else
        { 
            uart_deinit(UARTID);
            // port->end();
            return 0;
        }
}


long int RMCS2303::value(string input)
{ 
	string x;
    char a[9];
    int len;
    char *endptr;
    long int p;
	len=input.length();

	x=input.substr(7,len-10);  // Adjusted
    strncpy(a, x.c_str(), sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
	// x.toCharArray(a,len-9);

	p=strtoul(a,&endptr,16);
	return p;
}
