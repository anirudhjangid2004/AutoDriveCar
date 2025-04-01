import serial
import struct

def read_usb_message(port, baudrate=115200):
    ser = serial.Serial(port, baudrate, timeout=1)
    
    while True:
        if ser.in_waiting:
            data = ser.read(40) 
            if len(data) < 5:  
                print("Incomplete message received")
                continue 
            
            if data[0] != 0xFA :  
                continue
            
                
            msg_id = data[1]
            length = data[2]
            payload = data[3:3+length]
            received_checksum = data[3+length]
            
            # Compute checksum
            checksum = msg_id ^ length
            for byte in payload:
                checksum ^= byte
            
            if checksum != received_checksum:
                print("Checksum mismatch")
                continue
            
            if msg_id == 114:
                # encoder data
                encoders = []
                if length >= 16:
                    encoders = [struct.unpack('<i', payload[i:i+4])[0] for i in range(0, 16, 4)]
                
                # acceleration data
                acceleration = []
                if length >= 22:  
                    acceleration = [struct.unpack('<h', payload[i:i+2])[0] / 100.0 for i in range(16, 22, 2)]
                
                # gyroscope data
                gyroscope = []
                if length >= 28:
                    gyroscope = [struct.unpack('<h', payload[i:i+2])[0] / 100.0 for i in range(22, 28, 2)]
                
                print(f"Received Message ID: {msg_id}, Encoders: {encoders}, Acceleration: {acceleration}, Gyroscope: {gyroscope}")
    
if __name__ == "__main__":
    port = "/dev/ttyACM0"
    read_usb_message(port)