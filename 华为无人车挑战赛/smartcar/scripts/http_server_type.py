#!/usr/bin/env python
# -*- coding: UTF-8 -*-
from flask import Flask
from flask import request
import json
import base64
import datetime

import rospy
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Bool
from std_msgs.msg import Int64
import numpy as np

app = Flask(__name__)

@app.route("/dengfeng_detection_result", methods=['POST', 'GET'])
def webhook():
    
    data = request.values.to_dict()
    #has_follow_me = False
    # 位置信息
    bbox = data['bbox']
    for i in range(len(bbox)):
        if(bbox[i] == ']'):
            break
    pos = bbox[4:i]
    
    #[left, up, right, bottom] = pos.split(' ')
    #position = []    # 存放上下左右四个位置数值的 list
    cur_pos = ''    # 存放当前位置的 string
    last = ' '
    cur = ' '
    '''
    for j in range(len(pos)):
        cur = pos[j]
        if((last == ' ') and (cur == ' ')):    # 上一个和当前都是空格，不做修改
            pass
        elif((cur != ' ')):    # 当前不是空格，写入数字
            cur_pos = cur_pos + cur
        elif((last != ' ') and (cur == ' ')):    # 上一个不是空格，这个是，则上一个数已结束
            position.append(cur_pos)
            cur_pos = ''
        last = cur
    position.append(cur_pos)    # 最后一个数已结束，写入
    [left, up, right, bottom] = position
    
    left = int(left);up = int(up);right = int(right);bottom = int(bottom);
    print('位置信息：\n')
    print('左上：(%d, %d)\n'%(left, up))
    print('右下：(%d, %d)\n'%(right, bottom))
    #print('\n\n')
    '''

    # 置信度
    confidence = data['confidence']
    for i in range(len(confidence)):
        if(confidence[i] == ']'):
            break
    conf = confidence[3:i]
    conf = float(conf)
    
    # 类别
    cls = data['class']
    for i in range(len(cls)):
        if(cls[i] == '.'):
            break
    cls = cls[3:i]
    cls = int(cls)
    
    if(cls != 0 and conf > 0.6):    # 没有检测到标志，或者检测到的置信度太低
        detec_type = cls
        type_pub.publish(detec_type)
        print('置信度:')
        print(conf)
        print('\n')
        print('类别:')
        print(cls)
        print('\n')
    '''
    else:
        # 跟车牌位置信息
        center = [(left + right) // 2, (up + bottom) // 2]
        size = bottom - up
        dist = 119.0717/size    # 纵向距离
        offset = (center[0] - 640) * 0.14 / size    # 横向距离
        follow_info = [dist, offset]    # 目标的位置信息
        print('距离：%f\n' % dist)
        print('横向偏置：%f\n\n' % offset)
        # 发布：有标志牌
        has_follow_me = True
        follow_pub.publish(has_follow_me)
        # 发布：标志牌位置
        Pos.data = follow_info
        follow_where.publish(Pos)
    '''        
    return "OK!"

if __name__ == "__main__":
    # 初始化节点
    rospy.init_node('dengfeng_detection', anonymous=True)
    # 初始设置
    detec_type = Int64()    # 是否有目标
    type_pub = rospy.Publisher('detec_type', Int64, queue_size=1)    # 是否有目标
    #Pos = Float32MultiArray()    # 目标位置
    #follow_where = rospy.Publisher('follow_where', Float32MultiArray, queue_size=1)    # 目标位置

    app.run(host="0.0.0.0", port="8088")
