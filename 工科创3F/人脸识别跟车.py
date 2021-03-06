#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
from driver import driver
import time
import cv2
import math
faceCascade = cv2.CascadeClassifier('/home/pi/Desktop/haarcascade_frontalface_default.xml')
 
cap = cv2.VideoCapture(0)
cap.set(3,640) # set Width
cap.set(4,480) # set Height
d = driver()
d.setStatus(motor=0.0, servo=0.0, dist=0x00, mode="stop") 
while True:
    ret, img = cap.read()
    img = cv2.flip(img, -1)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,     
        scaleFactor=1.2,
        minNeighbors=5,     
        minSize=(15, 20)
    )
 
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
    if len(faces)>0:
        for (x,y,w,h) in faces:
            offset=(x+w/2-320)/320

            d.setStatus(motor=0.1, servo=offset, dist=0x00, mode="speed")
            time.sleep(0.05)
    print(offset)
    cv2.imshow('video',img)
    
    k = cv2.waitKey(30) & 0xff
    if k == 27: # press 'ESC' to quit
        break
 
cap.release()
cv2.destroyAllWindows()