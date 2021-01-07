#!/usr/bin/env python 
# -*- coding:utf-8 -*-

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

def sign(frame):
    img1_path = "/home/pi/Desktop/turnright.png"
    img2_path = "/home/pi/Desktop/turnleft.png"
    img3_path = "/home/pi/Desktop/go straight.png"
    cross=0
    img1 = Image.open(img1_path)
    img2 = Image.open(img2_path)
    img3 = Image.open(img3_path)
    # 计算局部敏感哈希值
    img1_phash = str(phash(img1))
    img2_phash = str(phash(img2))
    img3_phash = str(phash(img3))
#加载原图
    img=frame
    cv2.imshow("1",img)
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
    similary1=[]
    similary2=[]
    similary3=[]
    for con in contours:
    #轮廓转换为矩形
        rect=cv2.minAreaRect(con)
    #矩形转换为box
        box=np.int0(cv2.boxPoints(rect))
    #在原图画出目标区域
        cv2.drawContours(res,[box],-1,(0,0,255),2)
        #print([box])
    #计算矩形的行列
        h1=max([box][0][0][1],[box][0][1][1],[box][0][2][1],[box][0][3][1])
        h2=min([box][0][0][1],[box][0][1][1],[box][0][2][1],[box][0][3][1])
        l1=max([box][0][0][0],[box][0][1][0],[box][0][2][0],[box][0][3][0])
        l2=min([box][0][0][0],[box][0][1][0],[box][0][2][0],[box][0][3][0])
    #加上防错处理，确保裁剪区域无异常
        if h1-h2>0 and l1-l2>0:
        #裁剪矩形区域
            temp=img[h2:h1,l2:l1]
            i=i+1
        #显示裁剪后的标志
            #cv2.imshow('sign'+str(i),temp)   
            temp1 = Image.fromarray(cv2.cvtColor(temp,cv2.COLOR_BGR2RGB))
            #res_phash=str(phash(temp))
            distance1 = bin(phash(img1) ^ phash(temp1)).count('1')
            distance2= bin(phash(img2) ^ phash(temp1)).count('1')
            distance3= bin(phash(img3) ^ phash(temp1)).count('1')
            a=1 - distance1 / max(len(bin(phash(img1))), len(bin(phash(img1))))
            b=1 - distance2 / max(len(bin(phash(img2))), len(bin(phash(img2))))
            c=1 - distance3 / max(len(bin(phash(img3))), len(bin(phash(img3))))
            similary1.append(a)
            similary3.append(c)
            similary2.append(b)
    similary11=np.max(similary1)
    similary22=np.max(similary2)
    similary33=np.max(similary3)
    if similary11>0.8 and similary11>similary22 and similary11>similary33:
        print ("右转!")
        cross=1
    if similary22>0.8 and similary22>similary11 and similary22>similary33:
        print ("左转!")
        cross=2
    if similary33>0.8 and similary33>similary11 and similary33>similary22:
        print ("直行!")
        cross=3   
#显示画了标志的原图
    cv2.imshow('res',res)
    return cross

def decision():
    cap = cv2.VideoCapture(0)
    while True:
       ret, frame = cap.read()
       cv2.imshow("1",frame)
       cv2.waitKey(10)
       try:
           cross=sign(frame)
       except:
           print("no ")
    return 0

if __name__ == '__main__':
    decision()