#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
from std_msgs.msg import Bool
from std_msgs.msg import Int64
from geometry_msgs.msg import Twist
from std_msgs.msg import Float64
import time
import numpy as np

state = 0
turn_count=0
obs_flag = False

class M:
    def __init__(self, size):
        self.a=[]
        self.size=size
        for i in range(size):
            self.a.append(0)
    def add(self, sign):
        for j in range(self.size-1):
            self.a[j]=self.a[j+1]
        self.a[self.size-1]=sign
        b=np.array(self.a)
        count=np.bincount(b)
        print(self.a)
        if(np.max(count)<self.size/2):
            return 0
        else:
            return np.argmax(count)
m=M(5)            
class velocityDecide:
    def __init__(self):
        self.sign_flag = 0        #0 means using lane_vel, >0 means using lidar_vel
        
        self.lidar_vel = Twist()
        self.lidar_vel_right = Twist()
        self.lidar_vel_left = Twist()
        self.lidar_vel2 = Twist()
        self.cmd_vel = Twist()
        self.has_obs = Bool()
        self.turn_left=Bool()
        self.inf_flag=Bool()
        self.left_min=Float64()
        self.right_min=Float64()
        self.front=Float64()
        self.detec_type=Int64()
        
      
        rospy.init_node('velocity_decision', anonymous=True)        # 速度决策节点
        rospy.Subscriber('lidar_vel', Twist, self.lidarcallback)    # 雷达两侧闭环速度1
        rospy.Subscriber('lidar_vel2', Twist, self.lidar2callback)    # 雷达两侧闭环速度2
        #rospy.Subscriber('across', Bool, self.acrosscallback)    # 路口
        rospy.Subscriber('turn_left', Bool, self.turnleftcallback)    # 直角左转
        rospy.Subscriber('inf_flag', Bool, self.infcallback)
        rospy.Subscriber('front', Float64, self.frontcallback)    # 前向距离 obs and inf
        rospy.Subscriber('left_min', Float64, self.leftcallback)    # 左侧最短
        rospy.Subscriber('right_min', Float64, self.rightcallback)    # 右侧最短
        rospy.Subscriber('has_obs', Bool, self.obscallback)    # 是否有障碍物
        rospy.Subscriber('detec_type', Int64, self.deteccallback)    # 检测类型
        rospy.Subscriber('lidar_vel_right', Twist, self.lidar_right_callback)    # 雷达右侧闭环速度1
        rospy.Subscriber('lidar_vel_left', Twist, self.lidar_left_callback)    # 雷达左侧闭环速度1
        

        self.pub = rospy.Publisher('cmd_vel', Twist, queue_size=1)
        self.rate = rospy.Rate(10)
        
        

    def lidarcallback(self, msg):
        self.lidar_vel = msg 
    def lidar2callback(self, msg):
        self.lidar_vel2 = msg   
    def turnleftcallback(self, msg):
        self.turn_left=msg    
    def infcallback(self, msg):
        self.inf_flag=msg    
    def frontcallback(self, msg):
        self.front= msg
    def leftcallback(self, msg):
        self.left_min= msg
    def rightcallback(self, msg):
        self.right_min= msg
    def obscallback(self, msg):
        self.has_obs = msg
    def deteccallback(self, msg):
        self.detec_type=msg
    def lidar_right_callback(self, msg):
        self.lidar_vel_right = msg 
    def lidar_left_callback(self, msg):
        self.lidar_vel_left = msg 

    def spin(self):
        global state
        global count
        global turn_count
        global obs_flag
        global m
        while not rospy.is_shutdown():
            print('inf_flag: ',self.inf_flag.data)
            #print(self.right_min)
            #print(self.turn_left.data)
            if (self.has_obs.data == True):
                obs_flag = True
            if (self.detec_type.data == 1 and state==0):
                state=m.add(0)           
            elif (self.detec_type.data == 3 and (state==0 or state==1)):
                state=m.add(1)               
            elif (self.detec_type.data == 2 and (state==0 or state==2)):
                state=m.add(2)
            elif (self.detec_type.data == 4 and obs_flag == True):
                state=m.add(3)
            elif (self.detec_type.data == 5 and obs_flag == True):
                state=m.add(4)
            print(state)       
            if(state==0 or self.has_obs.data == True or (self.inf_flag.data == True and obs_flag == True)):
                #print("a")        
                self.cmd_vel.linear.x = 0
                self.cmd_vel.angular.z = 0
                self.pub.publish(self.cmd_vel)
            #elif(self.across.data==True and state==1):
            elif(state==1 and self.turn_left.data == False and turn_count < 2):
                #turnright###
                self.cmd_vel = self.lidar_vel_right
                
                self.pub.publish(self.cmd_vel)
                
            #elif (self.across.data==True and state==2):
            #elif (state==2 and self.turn_left.data == False):
            elif (state==2 or (turn_count >= 2 and state == 1)):
                #turnleft
                print("left lidar>>>")
                self.cmd_vel.linear.x = self.lidar_vel_left.linear.x
                self.cmd_vel.angular.z = self.lidar_vel_left.angular.z
                self.pub.publish(self.cmd_vel)
                   
            elif ((self.turn_left.data==True and state==1)and turn_count==0):
                #turnright kai huan
                print("turnright kai huan ------------------>>>>>>>>>>>>>>>>>>>")
                self.cmd_vel.linear.x = 1.0
                self.cmd_vel.angular.z = -45
                self.pub.publish(self.cmd_vel)
                self.rate.sleep()
                rospy.sleep(0.5)
                turn_count=turn_count+1     
                
            elif ((self.turn_left.data==True and state==1)and turn_count==1):
                #turnright kai huan
                print("turnright kai huan ------------------>>>>>>>>>>>>>>>>>>>")
                self.cmd_vel.linear.x = 0.9
                self.cmd_vel.angular.z = -40
                self.pub.publish(self.cmd_vel)
                self.rate.sleep()
                rospy.sleep(0.9)
                turn_count=turn_count+1  
            elif (state==3):
                if(self.front.data>3.5):                  
                    self.cmd_vel = self.lidar_vel_right
                    self.pub.publish(self.cmd_vel)
                    self.rate.sleep()
                elif(self.front.data<=3.5 and self.front.data>2.8):
                    
                    self.cmd_vel.linear.x = 1.4
                    self.cmd_vel.angular.z = 0
                    self.pub.publish(self.cmd_vel)
                    self.rate.sleep()
                elif(self.front.data<=2.8 and self.front.data>2.0):
                    print('3c')
                    self.cmd_vel.linear.x=1
                    self.cmd_vel.angular.z=45
                    self.pub.publish(self.cmd_vel)
                    self.rate.sleep()
                    rospy.sleep(1.0)

            elif (state==4):
                if(self.front.data>3.5): 
                    print("a")                
                    self.cmd_vel = self.lidar_vel_right
                    self.pub.publish(self.cmd_vel)
                    self.rate.sleep()
                elif(self.front.data<=3.5 and self.front.data>2.0):
                    print("b")
                    self.cmd_vel.linear.x = 1.4
                    self.cmd_vel.angular.z = 0
                    self.pub.publish(self.cmd_vel)
                    self.rate.sleep()
                elif(self.front.data<=1.9 and self.front.data>1.0):
                    print("4c")
                    self.cmd_vel.linear.x=1
                    self.cmd_vel.angular.z=45
                    self.pub.publish(self.cmd_vel)
                    self.rate.sleep()
                    rospy.sleep(1.6)
                else:
                    self.cmd_vel = self.lidar_vel_right
               
                    self.pub.publish(self.cmd_vel)
            else:
                #print("b")
                if (obs_flag == True):
                    self.cmd_vel = self.lidar_vel2
                else:
                    self.cmd_vel = self.lidar_vel
                self.pub.publish(self.cmd_vel)
            self.rate.sleep()

if __name__ == '__main__':
   
    try:
        decide = velocityDecide()
        
        decide.spin()
    except rospy.ROSInterruptException:
        pass

    
        
