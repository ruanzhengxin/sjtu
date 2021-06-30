#!/usr/bin/env python
# -*- coding: utf-8 -*-
# BEGIN ALL
import serial
import time
ser=serial.Serial('/dev/ttyACM0','9600',timeout=5)
ser.flushInput()
ser.flushOutput()
ser1 = serial.Serial('/dev/ttyUSB0',9600,timeout=1)
ser1.flushInput()
ser1.flushOutput()
def main():
    destination=[3101.59000,12126.24000]
    direction=0                       
    while True:
        count=ser.inWaiting()
        if count!=0:
            recv=ser.read(ser.in_waiting)
            if recv[17]== 'A':
                gps_data=[float(recv[19:29]),float(recv[32:43])]
            else:
                gps_data=[0,0]
        else:
            continue
        print(gps_data)
        if abs(gps_data[0]-destination[0])<0.01 and abs(gps_data[1]-destination[1])<0.01:
            direction=0
        elif gps_data==[0,0]:
            direction=0
        else:
            direction=1
        send = chr(int(direction))
        ser1.write(send.encode())
        time.sleep(0.1)
        
if __name__=='__main__':
    main()   
        
    
