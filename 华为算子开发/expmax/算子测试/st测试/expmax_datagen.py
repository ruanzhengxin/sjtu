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


def expmax(name, shape, src_type, scale):
    """
    none
    """
    sys.stdout.write("Info: writing input for %s...\n" % name)
    shape_str = ""
    for dim in shape:
        shape_str += str(dim) + "_"
    feature_name = shape_str + src_type

    input1 = np.random.uniform(0, 2, shape).astype(src_type)
    dumpData(input1, name + "_input_" + feature_name + ".data",
             fmt="binary", data_type=src_type,
             path="../data/" + name + "/" + feature_name)

    input1 = torch.FloatTensor(input1)
    b = torch.max(input1, -1, keepdim=True)[0]
    b = b.half()
    output = np.array(np.exp(np.multiply(scale, np.subtract(input1, b))))
    dumpData(output, name + "_output_" + feature_name + ".data",
             fmt="binary", data_type=src_type,
             path="../data/" + name + "/" + feature_name)
    sys.stdout.write("Info: writing output for %s done!!!\n" % name)


def gen_expmax_data():
    """
    none
    """
    expmax("expmax", (5, 10, 10, 4), "float16", 3.)
    expmax("expmax", (2, 5, 5, 5), "float16", 4.)
    expmax("expmax", (6, 10, 10, 15), "float32", 1.)


if __name__ == "__main__":
    gen_expmax_data()
