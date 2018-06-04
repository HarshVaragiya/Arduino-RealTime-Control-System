import keyboard 
import numpy as np
import time 
import serial           
ser = serial.Serial('COM5', 57600)                                        # change according to your serial port and baud rate 
time.sleep(2)                                                             # wait till arduino resets 

def transmit(control_signal): 
    print("Transmitting : " + str(control_signal))
    tx = chr(int(control_signal))
    ser.write(tx.encode())
    
while True:
    control_output = np.uint8(0)
    
    if keyboard.is_pressed('w'):
        control_output = 0x04
    elif(keyboard.is_pressed('s')):
        control_output = 0x08
    
    # 0000 XX 01 bit math for slightly faster operation
    # and with 1111 1100 or with 0xCS
    
    if(keyboard.is_pressed('a')):
        control_output = ((control_output & 0xFC) | 0x01)
    elif(keyboard.is_pressed('d')):
        control_output = ((control_output & 0xFC) | 0x02)

    transmit(control_output+1)                                           # some thing takes place when we transmit 0000 0000
                                                                         # so to avoid add 1 to everything , then reduce 1 from all
                                                                         # when arduino recieves data.
    if(keyboard.is_pressed('p')):
        break
    time.sleep(0.1)
ser.close()
