
import serial
import sys

# Constants for the protocol
START_BYTE = 0xFA  # Start byte
STOP_BYTE = 0xFB   # Stop byte

def hex_string_to_bytes(hex_string):
    """Convert a hex string (e.g., '6D 04 FA FF') to a byte array."""
    try:
        return bytearray(int(byte, 16) for byte in hex_string.split())
    except ValueError:
        print("Error: Invalid hex string format")
        return None

def calculate_checksum(data):
    """Calculate checksum as the XOR of all bytes."""
    checksum = 0
    for byte in data:
        checksum ^= byte
    return checksum


def send_data(serial_port, data):
    """Send data over tiny USB with start byte, checksum, and stop byte."""
    # Convert input string to bytes
    data_bytes = data.encode('utf-8')
    checksum = calculate_checksum(data_bytes)
    
    # Construct the packet
    packet = bytearray([START_BYTE]) + data_bytes + bytearray([checksum, STOP_BYTE])
    
    # Send the packet
    serial_port.write(packet)
    print(f"Sent: {packet}")

def find_start_byte(serial_port):
    """Find the start byte in the incoming data stream."""
    while True:
        byte = serial_port.read(1)
        if not byte:
            print("Error: No data received")
            return None
        if byte[0] == START_BYTE:
            return byte
            
def receive_data(serial_port):
    """Receive data from tiny USB, validate checksum, and print the payload."""
    # Read the start byte
    start_byte = serial_port.read(1)
    if not start_byte or start_byte[0] != START_BYTE:
        print("Error: Invalid start byte")
        return
    
    # Read the payload until the checksum and stop byte
    payload = bytearray()
    while True:
        byte = serial_port.read(1)
        if not byte:
            print("Error: Incomplete packet")
            return
        if byte[0] == STOP_BYTE:
            break
        payload.append(byte[0])
    
    # Extract the checksum
    if len(payload) < 1:
        print("Error: Missing checksum")
        return
    received_checksum = payload[-1]
    payload = payload[:-1]
    
    # Validate the checksum
    calculated_checksum = calculate_checksum(payload)
    if received_checksum != calculated_checksum:
        print("Error: Checksum mismatch")
        return
    
    # Print the received payload
    print(f"Received: {payload.decode('utf-8')}")

def main():
    # Open the serial port
    try:
        serial_port = serial.Serial('/dev/ttyACM0re', baudrate=115200, timeout=1)
    except serial.SerialException as e:
        print(f"Error: Could not open serial port: {e}")
        sys.exit(1)
    
    print("Tiny USB Driver")
    print("Enter 'send <data>' to send data or 'receive' to receive data.")
    
    while True:
        command = input("> ").strip()
        if command.startswith("send "):
            data = command[5:]
            send_data(serial_port, data)
        elif command == "receive":
            receive_data(serial_port)
        elif command == "exit":
            print("Exiting...")
            break
        else:
            print("Invalid command. Use 'send <data>', 'receive', or 'exit'.")
    
    serial_port.close()

if __name__ == "__main__":
    main()

