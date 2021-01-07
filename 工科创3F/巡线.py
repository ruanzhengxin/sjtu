#!/usr/bin/python
# -*- coding: utf-8 -*-

from driver import driver
import time
import cv2
import numpy as np
import math
def run_picar():
    print("==========piCar Client Start==========")
                                            # 打开摄像头
    d = driver()
    d.setStatus(motor=0.0, servo=0.0, dist=0x00, mode="stop")
    cap = cv2.VideoCapture(0)
    time.sleep(2)
    count=0
    state=0
    detla_offset=0
    old_control=0
    while True:
       ret, frame = cap.read()
    # 转化为灰度图
       #frame1=frame[30:230,120:520]
       gray= cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
       #gray=gray1[30:220,120:520]
    # 大津法二值化
       #result = cv2.GaussianBlur(gray, (3,3), 0)
       retval, dst = cv2.threshold(gray, 0, 255, cv2.THRESH_OTSU)
    # 膨胀，白区域变大
       #dst1 = cv2.dilate(dst, None, iterations=2)
       dst1 = cv2.erode(dst, None, iterations=3)
    # # 腐蚀，白区域变小
       dst=dst1[0:160,170:470]
       #cv2.imshow("1",gray)
       cv2.imshow("0",dst)
       #cv2.imshow("3",frame)
       cv2.waitKey(10)
      
       #print(b,state)
       
       color = dst[30]
       #找到黑色的像素点个数
       black_count = np.sum(color == 0)
       # 找到黑色的像素点索引
       black_index = np.where(color == 0)
       # 防止white_count=0的报错
       if black_count == 0:
           black_count = 1
       # 找到色像素的中心点位置
       try:
           center = (black_index[0][black_count - 1] + black_index[0][0]) / 2
       # 计算出center与标准中心点的偏移量
           direction = (center - 150)/30
           offset=math.atan(direction)
           kp=0.45
           kd=2
           different=offset-detla_offset
           control=kp*offset+kd*different
           if control>1:
               control=1
           if control<-1:
               control=-1
           detla_offset=offset
          #print(offset)
              #print(control)
           if control<0.1 and control>-0.1:
               d.setStatus(motor=0.25, servo=0,dist=0x00,mode="speed")
           else:
               d.setStatus(motor=0.1, servo=control,dist=0x00,mode="speed")
           time.sleep(0.01)
           old_control=control
       except:
           control=old_control
           print(control)
           d.setStatus(motor=0.1, servo=control,dist=0x00,mode="speed")
           time.sleep(0.01)
       
      
    return 0
               
    
if __name__ == '__main__':
    run_picar()

