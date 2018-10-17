#!bin/usr/python3
import keyboard 
import numpy as np
import time 
import os 

try:
    import serial
except ImportError:
    print("Error Importing Pyserial Library          ")
    print("Try Installing it with this command       ")
    print(" linux   - pip install pyserial           ")
    print(" windows - python -m pip install pyserial ")
    print(" if you get error installing it, try uninstalling 'serial' and 'pyserial' library using this command")
    print(" linux   - pip uninstall serial,pyserial  ")
    print(" windows - python -m pip uninstall serial,pyserial ")
    print(" Then Try installing it again.")
    exit()

ser = serial.Serial('COM5', 57600)                                        # change according to your serial port and baud rate 

time.sleep(2)                                                             # wait till arduino resets 

def transmit(control_signal): 
    print("Transmitting : " + str(control_signal))
    tx = chr(int(control_signal+1))
    ser.write(tx.encode())
    
while True:
    control_output = np.uint8(0)
    
    if keyboard.is_pressed('w'):
        control_output = 0x01
    elif(keyboard.is_pressed('s')):
        control_output = 0x02
    
    # 0000 XX 01 bit math for slightly faster operation
    # and with 1111 1100 or with 0xCS

    transmit(control_output)  

    if(keyboard.is_pressed('p')):
        transmit(0x04)
        break
    time.sleep(0.1)
ser.close()
