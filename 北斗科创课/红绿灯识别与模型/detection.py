#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
from __future__ import absolute_import, division, print_function
import os
import sys
import cv2
import tensorflow as tf
import numpy as np
import h5py
import serial
import time
ser1 = serial.Serial('/dev/ttyUSB0',9600,timeout=1)
ser1.flushInput()
ser1.flushOutput()

class sjtu_detection:  
    def __init__(self):
        currentpath, _ = os.path.split(os.path.abspath(sys.argv[0]))
        self.modelpath = currentpath
        self.prob_threshold = 0.3
        self.nms_iou_threshold = 0.3
        self.predict_fn = tf.contrib.predictor.from_saved_model(self.modelpath, signature_def_key='predict_object')
        with h5py.File(os.path.join(self.modelpath, 'index'), 'r') as h5f:
            self.labels_list = h5f['labels_list'][:]

    def predict(self, img):
        img = img[np.newaxis, :, :, :]
        output = self.predict_fn({'images':img})        
        num_boxes = len(output['detection_classes'])
        classes = []
        boxes = []
        scores = []
        result_return = dict()
        for i in range(num_boxes):
            if output['detection_scores'][i] > self.prob_threshold:
                class_id = output['detection_classes'][i] - 1
                classes.append(self.labels_list[int(class_id)])
                boxes.append(output['detection_boxes'][i])
                scores.append(output['detection_scores'][i])
        ##########add NMS#######################################
        bounding_boxes = boxes
        confidence_score = scores
        # Bounding boxes
        boxes = np.array(bounding_boxes)
        picked_boxes = []
        picked_score = []
        picked_classes = []
        if len(boxes) != 0:
            # coordinates of bounding boxes
            start_x = boxes[:, 0]
            start_y = boxes[:, 1]
            end_x = boxes[:, 2]
            end_y = boxes[:, 3]
            # Confidence scores of bounding boxes
            score = np.array(confidence_score)
            # Picked bounding boxes
            # # Compute areas of bounding boxes
            areas = (end_x - start_x + 1) * (end_y - start_y + 1)
            # Sort by confidence score of bounding boxes
            order = np.argsort(score)
            # Iterate bounding boxes
            while order.size > 0:
                # The index of largest confidence score
                index = order[-1]
                # Pick the bounding box with largest confidence score
                picked_boxes.append(bounding_boxes[index])
                picked_score.append(confidence_score[index])
                picked_classes.append(classes[index])
                # Compute ordinates of intersection-over-union(IOU) 
                x1 = np.maximum(start_x[index], start_x[order[:-1]])
                x2 = np.minimum(end_x[index], end_x[order[:-1]])                
                y1 = np.maximum(start_y[index], start_y[order[:-1]])
                y2 = np.minimum(end_y[index], end_y[order[:-1]])
                # Compute areas of intersection-over-union
                w = np.maximum(0.0, x2 - x1 + 1)
                h = np.maximum(0.0, y2 - y1 + 1)
                intersection = w * h
                # Compute the ratio between intersection and union
                ratio = intersection / (areas[index] + areas[order[:-1]] - intersection)
                left = np.where(ratio < self.nms_iou_threshold) 
                order = order[left] 
        
        result_return['detection_classes'] = picked_classes
        result_return['detection_boxes'] = picked_boxes
        result_return['detection_scores'] = picked_score
        return result_return

    def visualize(self, img, result):
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
        detection_classes = result['detection_classes']
        detection_boxes = result['detection_boxes']
        if detection_boxes:
            for i in range(len(detection_boxes)):
                start_x = detection_boxes[i][0]
                start_y = detection_boxes[i][1]
                end_x = detection_boxes[i][2]
                end_y = detection_boxes[i][3]
                detection_class = detection_classes[i].decode('utf-8')
                cv2.rectangle(img, (int(start_y), int(start_x)), (int(end_y), int(end_x)), (0, 0, 255))
                font = cv2.FONT_HERSHEY_SIMPLEX
                if detection_class == 'off':
                    detection_class = 'green'
                if detection_class == 'green':
                    direction=1
                    send = chr(int(direction))
                    ser1.write(send.encode())
                elif detection_class == 'red':
                    direction=0
                    send = chr(int(direction))
                    ser1.write(send.encode())
                else:
                    direction=0
                    send = chr(int(direction))
                    ser1.write(send.encode())
                cv2.putText(img, detection_class, (int(start_y), int(start_x)), font, 1, (0, 0, 255))
        return img

'''
class trafficLightDetector:
    def __init__(self):
  
        self.detector = sjtu_detection()
        

    def callback(self, imgmsg):
       # img = self.cvb.imgmsg_to_cv2(imgmsg)
        img = imgmsg
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        output = self.detector.predict(img)
        outimg = self.detector.visualize(img, output)
        self.has_red_light = False
        self.has_green_light = False
        for detection_class in output['detection_classes']:
            detection_class = detection_class.decode('utf-8')
            if detection_class == "red":
                self.has_red_light = True
            elif detection_class == "green":
                self.has_green_light = True             
        self.red_pub.publish(self.has_red_light)
        self.green_pub.publish(self.has_green_light)
        cv2.imshow("tracffic_light", outimg)
        cv2.waitKey(1)
'''
if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    detector = sjtu_detection()
    while True:
        ret, img = cap.read()
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        output = detector.predict(img)
        outimg = detector.visualize(img, output)
        cv2.imshow("tracffic_light", outimg)
        cv2.waitKey(1)
    cap.release()

    
    
    
    
    
    
