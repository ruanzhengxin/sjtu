#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#小车跟随距离最近的障碍物

import rospy
from std_msgs.msg import Bool
from sensor_msgs.msg import LaserScan
import serial
import time

Port = '/dev/ttyUSB1'
ser = serial.Serial(Port,9600,timeout=1)
ser.flushInput()
ser.flushOutput()
class rplidarDetector:
    def __init__(self):
        rospy.init_node('rplidar_detection', anonymous=True)
        rospy.Subscriber('/scan', LaserScan, self.callback)
        print 'LiDAR is OK'
       
    def obstacle_follower(self, msg):
        min_distance = 0.6
        min_distance_index = 0
        direction=0
        for i in range (0,360):
            if msg.ranges[i] < min_distance and msg.ranges[i] > 0.3:
                min_distance = msg.ranges[i]
                min_distance_index = i
        if min_distance == 0.6:
            direction=0
        elif min_distance_index >= 337:
            direction = (1 + 4) % 8
        else:
            direction =(( (min_distance_index + 23) // 45 )+1 + 4) % 8  
	print 'min_dis = ', min_distance        
	return direction

    def callback(self, msg):
        direction = self.obstacle_follower(msg)
        print (direction) 
	#print('hello')     
        send = chr(int(direction))
        ser.write(send.encode())
        str1 = ser.readline().decode()
        if(str1 != ""):
            print("str1",str1)
        #time.sleep(0.8)
        #send = chr(0)

if __name__ == '__main__':
    try:
        detector = rplidarDetector()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
