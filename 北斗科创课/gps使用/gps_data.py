#!/usr/bin/env python
# -*- coding: utf-8 -*-
# BEGIN ALL
import serial
import time
ser=serial.Serial('/dev/ttyACM0','9600',timeout=5)
ser.flushInput()
ser.flushOutput()
def main():                       
    while True:
        count=ser.inWaiting()
        if count!=0:
            recv=ser.read(ser.in_waiting)
            if recv[17]== 'A':
                print(recv[19:29],recv[32:43])
            elif recv[17]=='V':
                print("nan")
            else:
                continue
        time.sleep(0.1)
if __name__=='__main__':
    main()   
        
    
