#!/usr/bin/python
# -*- coding: utf-8 -*-

from driver import driver
from queue import Queue
import time
import cv2
import numpy as np
import math
from functools import reduce
from PIL import Image

         
def phash(img):
    """
    :param img: 图片
    :return: 返回图片的局部hash值
    """
    img = img.resize((8, 8), Image.ANTIALIAS).convert('L')
    avg = reduce(lambda x, y: x + y, img.getdata()) / 64.
    hash_value=reduce(lambda x, y: x | (y[1] << y[0]), enumerate(map(lambda i: 0 if i < avg else 1, img.getdata())), 0)

    return hash_value

def run_picar():
    print("==========piCar Client Start==========")
                                            # 打开摄像头
    d = driver()
    d.setStatus(motor=0.0, servo=0.0, dist=0x00, mode="stop")
    cap = cv2.VideoCapture(0)
    state=0
    detla_offset=0
    old_control=0
    que=Queue(maxsize=6)
    cross=0
    choice=0
    c=[]
    t=0
    while True:
        ret, frame = cap.read()
        cv2.imshow("original", frame)
        if cv2.waitKey(1) & 0xFF == ord('s'):
            cv2.destroyWindow("original")
            break
        time.sleep(0.1)
        
    img1_path = "/home/pi/Desktop/turnright.png"
    img2_path = "/home/pi/Desktop/turnleft.png"
    cross=0

    img1 = Image.open(img1_path)
    img2 = Image.open(img2_path)
    # 计算局部敏感哈希值
    img1_phash = str(phash(img1))
    img2_phash = str(phash(img2))
    
    while True:
        ret, frame = cap.read()

        try:
            cross=0
            img=frame[200:400,70:570]

            hsv=cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
            #提取蓝色区域
            blue_lower=np.array([100,50,50])
            blue_upper=np.array([124,255,255])
            mask=cv2.inRange(hsv,blue_lower,blue_upper)
    #模糊
            blurred=cv2.blur(mask,(9,9))
    #二值化
            ret,binary=cv2.threshold(blurred,127,255,cv2.THRESH_BINARY)
    #使区域闭合无空隙
            kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (21, 7))
            closed = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)
            erode=cv2.erode(closed,None,iterations=4)
            dilate=cv2.dilate(erode,None,iterations=4)
            image,contours, hierarchy=cv2.findContours(dilate.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
            i=0
            res=img.copy()
            similary11=0
            similary22=0
            for con in contours:
    #轮廓转换为矩形
                rect=cv2.minAreaRect(con)
                box=np.int0(cv2.boxPoints(rect))
                h1=max([box][0][0][1],[box][0][1][1],[box][0][2][1],[box][0][3][1])
                h2=min([box][0][0][1],[box][0][1][1],[box][0][2][1],[box][0][3][1])
                l1=max([box][0][0][0],[box][0][1][0],[box][0][2][0],[box][0][3][0])
                l2=min([box][0][0][0],[box][0][1][0],[box][0][2][0],[box][0][3][0])
       
    #加上防错处理，确保裁剪区域无异常
                if h1-h2>0 and l1-l2>0 and h1-h2<50 and l1-l2<50:
        #裁剪矩形区域
                    temp=img[h2:h1,l2:l1]
                    i=i+1
        #显示裁剪后的标志
                    cv2.drawContours(res,[box],-1,(0,0,255),2)
                    temp1 = Image.fromarray(cv2.cvtColor(temp,cv2.COLOR_BGR2RGB))
                    distance1 = bin(phash(img1) ^ phash(temp1)).count('1')
                    distance2= bin(phash(img2) ^ phash(temp1)).count('1')
                    a = 1 - distance1 / max(len(bin(phash(img1))), len(bin(phash(img1))))
                    b = 1 - distance2 / max(len(bin(phash(img2))), len(bin(phash(img2))))
                    if a>similary11:
                        similary11=a
                    if a>similary22:
                        similary22=b    
            if similary11>0.8 and similary11>similary22:
        #print ("右转")
                cross=1
            if similary22>0.8 and similary22>similary11:
        #print ("左转")
                cross=2
#显示画了标志的原图
            cv2.imshow('res',res)
            cv2.waitKey(10)
        except:
            cross=0 #continue
          
        if que.full()==False:
            que.put(cross)
        else:
            que.get()
            que.put(cross)
        t=0
        tmp=0
       
        while t<que.qsize():
            tmp=que.get()
            c.append(tmp)
            que.put(tmp)
            t=t+1
        counts = np.bincount(c)
        choice=np.argmax(counts)
        print(choice)
        #print(c)
        c=[]
        if choice==1:
            d.setStatus(motor=0.075, servo=-1, dist=0x00, mode="speed")
            time.sleep(0.4)         
            state=0
        elif choice==2:
            d.setStatus(motor=0.075, servo=1, dist=0x00, mode="speed")
            time.sleep(0.3)          
            state = 0
        elif choice==0: #巡线
            ret, frame = cap.read()
    # 转化为灰度图
            frame1=frame[0:160,170:470]
            gray= cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)
    # 大津法二值化
            retval, dst = cv2.threshold(gray, 0, 255, cv2.THRESH_OTSU)
            dst = cv2.erode(dst, None, iterations=3)
    # # 腐蚀，白区域变小
            cv2.imshow("0",dst)
            cv2.waitKey(10)
            b=np.sum(dst==0)
            if b > 12000 and state == 0: #斑马线
                d.setStatus(motor=0.0, servo=0.0, dist=0x00, mode="stop")
                time.sleep(3)
                d.setStatus(motor=0.1, servo=0.0, dist=0x00, mode="speed")
                time.sleep(0.03)
                state=1
            color = dst[30]
            length=30
            i=1
       #找到黑色的像素点个数
            black_count = np.sum(color == 0)
       # 找到黑色的像素点索引
            black_index = np.where(color == 0)
       # 防止white_count=0的报错
            while black_count == 0 and i<14:
                black_count = np.sum(dst[30+10*i])
                black_index = np.where(dst[30+10*i] == 0)
                length=30+10*i
                i=i+1
            if black_count == 0:
                black_count = 1
       # 找到色像素的中心点位置
            try:
                center = (black_index[0][black_count - 1] + black_index[0][0]) / 2
       # 计算出center与标准中心点的偏移量
                direction = (center - 150)/length
                offset=math.atan(direction)
                kp=0.65
                kd=0
                different=offset-detla_offset
                control=kp*offset+kd*different
                if control>1:
                    control=1
                if control<-1:
                    control=-1
                detla_offset=offset
                d.setStatus(motor=0.1, servo=control,dist=0x00,mode="speed")
                old_control=control
            except:
                control=old_control
                d.setStatus(motor=0.1, servo=control,dist=0x00,mode="speed")
    return 0
               
    
if __name__ == '__main__':
    
    run_picar()

