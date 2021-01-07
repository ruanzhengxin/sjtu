#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
from std_msgs.msg import Bool
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Int64
from geometry_msgs.msg import Twist
from std_msgs.msg import Float64

last_offset=0
last_right_offset=0
last_left_offset=0
class rplidarDetector:
    def __init__(self):
        rospy.init_node('rplidar_detection', anonymous=True)
        rospy.Subscriber('/scan', LaserScan, self.callback)
        self.pub = rospy.Publisher('lidar_vel', Twist, queue_size=1)
        self.pubvel2 = rospy.Publisher('lidar_vel2', Twist, queue_size=1)
        self.pub1 = rospy.Publisher('across', Bool, queue_size=1)
        self.pub2 = rospy.Publisher('front', Float64, queue_size=1)
        self.pub3 = rospy.Publisher('left_min', Float64, queue_size=1)
        self.pub4 = rospy.Publisher('right_min',Float64, queue_size=1)
        self.pub5 = rospy.Publisher('turn_left', Bool, queue_size=1)
        self.pub6 = rospy.Publisher('inf_flag', Bool, queue_size=1)
        self.pub_right = rospy.Publisher('lidar_vel_right', Twist, queue_size=1)
        self.pub_left = rospy.Publisher('lidar_vel_left', Twist, queue_size=1)
        print 'LiDAR is OK'

    def road_detection(self, msg):
        #雷达正前方为720

        turn_left=False
        inf_flag = True
        ###################################### xun xian ##############
        right_min1 = 25
        right_min_index1 = 480
        for i in range(480,660):  #15-60
            if msg.ranges[i] < right_min1 and msg.ranges[i] > 0.05:
                right_min1 = msg.ranges[i]
                right_min_index1 = i
        
        left_min1 = 25
        left_min_index1 = 960
        for i in range(960, 780,-1):
            if msg.ranges[i] < left_min1 and msg.ranges[i] > 0.05:
                left_min1 = msg.ranges[i]
                left_min_index1 = i
                
        ######################### lu kou #############################
        right_cross = 25
        right_cross_index = 480
        for i in range(540,660):   #15-45
            if msg.ranges[i] < right_cross and msg.ranges[i] > 0.05:
                right_cross = msg.ranges[i]
                right_cross_index = i
        
        left_cross = 25
        left_cross_index = 960
        for i in range(900, 780,-1):
            if msg.ranges[i] < left_cross and msg.ranges[i] > 0.05:
                left_cross = msg.ranges[i]
                left_cross_index = i
        if (left_cross>1 and left_cross>1):
            across = True
        else:
            across = False
        ###################### 路口 ############################
        front = 25 
        front_index = 730
        for i in range(730, 710, -1):  # +2.5 to -2.5
            
            if msg.ranges[i] < front and msg.ranges[i] > 0.05:
                front  = msg.ranges[i]
                front_index = i
                
        ############## obs and inf ###############################
        front_min = 25
        front_min_index = 730
        for i in range(760, 680, -1):  # +10 to -10
            
            if msg.ranges[i] < front_min and msg.ranges[i] > 0.05:
                front_min  = msg.ranges[i]
                front_min_index = i
            if(msg.ranges[i] != float('inf')):
                inf_flag = False
        #print('*****************************')
        #print('front: '+str(front_min))
        ####前方距离

        #print('left_min :'+str(left_min1)+'\nright_min:'+str(right_min1))
        offset = left_min1-right_min1
        if (left_min1>1.0 and left_min1<1.5 and front>1.0 and front<1.5):
            turn_left=True
        else:
            turn_left=False 
        return offset,across,front,left_min1, right_min1,turn_left, inf_flag

    def callback(self, msg):
        global last_offset, last_right_offset, last_left_offset
        offset,across,front,left_min1, right_min1,turn_left,inf_flag = self.road_detection(msg)
        ############## xun shuang xian ################
        twist = Twist() 
        twist.angular.z = offset * 90  #-last_offset*90*0.08
        if(twist.angular.z>45):
            twist.angular.z=45
        elif(twist.angular.z<-45):
            twist.angular.z=-45
        twist.linear.x=1.0
        last_offset=offset
        
        ############## xun you xian ###################
        right_offset = 0.6 - right_min1    # nei 0.52, wai 0.6
        twist_right = Twist() 
        twist_right.angular.z = right_offset * 200  #-last_right_offset*90*0.08
        if(twist_right.angular.z>45):
            twist_right.angular.z=45
        elif(twist_right.angular.z<-45):
            twist_right.angular.z=-45
        twist_right.linear.x = 0.9
        last_right_offset=right_offset
        
        ############### xun zuo xian #################
        left_offset = left_min1 - 0.6     # nei 0.52, wai 0.6
        twist_left = Twist() 
        twist_left.angular.z = left_offset * 230 #-last_left_offset*200*0.08
        if(twist_left.angular.z>45):
            twist_left.angular.z=45
        elif(twist_left.angular.z<-45):
            twist_left.angular.z=-45
        twist_left.linear.x = 0.9
        last_left_offset=left_offset
       
        self.pub.publish(twist)
        twist.linear.x=1.5
        self.pubvel2.publish(twist)
        self.pub1.publish(across)
        self.pub2.publish(front)
        self.pub3.publish(left_min1)
        self.pub4.publish(right_min1)
        self.pub5.publish(turn_left)
        self.pub6.publish(inf_flag)
        self.pub_right.publish(twist_right)
        self.pub_left.publish(twist_left)

if __name__ == '__main__':
    try:
        detector = rplidarDetector()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
