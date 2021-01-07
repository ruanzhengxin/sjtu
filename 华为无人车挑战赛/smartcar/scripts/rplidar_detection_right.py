#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
from std_msgs.msg import Bool
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Int64
from geometry_msgs.msg import Twist
from std_msgs.msg import Float64

last_offset=0
class rplidarDetector:
    def __init__(self):
        rospy.init_node('rplidar_detection_right', anonymous=True)
        rospy.Subscriber('/scan', LaserScan, self.callback)
        self.pub = rospy.Publisher('lidar_vel_right', Twist, queue_size=1)
        #self.pub1 = rospy.Publisher('across', Bool, queue_size=1)
        #self.pub2 = rospy.Publisher('front', Float64, queue_size=1)
        #self.pub3 = rospy.Publisher('left_min', Float64, queue_size=1)
        #self.pub4 = rospy.Publisher('right_min',Float64, queue_size=1)
        #self.pub5 = rospy.Publisher('turn_left', Bool, queue_size=1)
        print 'LiDAR_right is OK'

    def road_detection(self, msg):
        #雷达正前方为720
        #across = False    # 判断路口
        #turn_left=False
        
        ############################ 找右侧距离最近的点（15-60度范围内）
        right_min1 = 25
        right_min_index1 = 480
        for i in range(480,660):#480 660
            if msg.ranges[i] < right_min1 and msg.ranges[i] > 0.05:
                right_min1 = msg.ranges[i]
                right_min_index1 = i
      
        offset = 0.52 - right_min1
        return offset, right_min1

    def callback(self, msg):
        global last_offset
        offset = self.road_detection(msg)[0]
        twist = Twist() 
        #twist.linear.x = 0.35#0.3
        twist.angular.z = offset * 200-last_offset*100*0.08
        if(twist.angular.z>45):
            twist.angular.z=45
        elif(twist.angular.z<-45):
            twist.angular.z=-45
        twist.linear.x=1
        last_offset=offset
        self.pub.publish(twist)
        
        #twist.linear.x=0.7
        #self.pubvel2.publish(twist)
        #self.pub1.publish(self.road_detection(msg)[1])
        #self.pub2.publish(self.road_detection(msg)[2])
        #self.pub3.publish(self.road_detection(msg)[3])
        #self.pub4.publish(self.road_detection(msg)[4])
        #self.pub5.publish(self.road_detection(msg)[5])

if __name__ == '__main__':
    try:
        detector = rplidarDetector()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
