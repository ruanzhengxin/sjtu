"""
Copyright (C) 2020. Huawei Technologies Co., Ltd. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the Apache License Version 2.0.You may not use this file
except in compliance with the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
Apache License for more details at
http://www.apache.org/licenses/LICENSE-2.0

"""
import numpy as np
import sys
from dataFormat import *
import torch


def accum(name, flow, img_shape, src_type):
    """
    none
    """
    sys.stdout.write("Info: writing input for %s...\n" % name)
    shape_str = ""
    for dim in flow:
        shape_str += str(dim) + "_"
    feature_name = shape_str + src_type
    input1 = np.random.uniform(0, 1, flow).astype(src_type)
    dumpData(input1, name + "_input_" + feature_name + ".data",
             fmt="binary", data_type=src_type,
             path="../data/" + name + "/" + feature_name)
    dst_w, dst_h = (img_shape[3], img_shape[2])
    src_h, src_w = (flow[2], flow[3])
    scale_x = float(src_w) / dst_w
    scale_y = float(src_h) / dst_h


    dst = np.zeros((flow[0], flow[1], dst_h, dst_w), dtype=src_type)
    for i in range(flow[0]):
        for n in range(flow[1]):
            for dst_y in range(dst_h):
                for dst_x in range(dst_w):
                    src_x = (dst_x + 0.5) * scale_x - 0.5
                    src_y = (dst_y + 0.5) * scale_y - 0.5
                    src_x_0 = int(np.floor(src_x))
                    src_y_0 = int(np.floor(src_y))
                    src_x_1 = min(src_x_0 + 1, src_w - 1)
                    src_y_1 = min(src_y_0 + 1, src_h - 1)
                    value0 = (src_x_1 - src_x) * input1[src_y_0, src_x_0, n] + \
                             (src_x - src_x_0) * input1[src_y_0, src_x_1, n]
                    value1 = (src_x_1 - src_x) * input1[src_y_1, src_x_0, n] + \
                             (src_x - src_x_0) * input1[src_y_1, src_x_1, n]
                    dst[i, n, dst_y, dst_x] = int((src_y_1 - src_y) * value0 + (src_y - src_y_0) * value1)
    dumpData(dst, name + "_output_" + feature_name + ".data",
             fmt="binary", data_type=src_type,
             path="../data/" + name + "/" + feature_name)
    sys.stdout.write("Info: writing output for %s done!!!\n" % name)


def gen_accum_data():
    """
    none
    """
    accum("accum", (5, 4, 10, 10), (5, 4, 20, 20), "float16")
    accum("accum", (2, 5, 5, 5), (2, 5, 10, 5), "float16")
    accum("accum", (6, 10, 10, 15), (6, 10, 20, 30), "float32")


if __name__ == "__main__":
    gen_accum_data()
