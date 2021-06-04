# # -*- coding:utf-8 -*-
import sys
from op_test_frame.ut import BroadcastOpUT
import numpy as np
ut_case = BroadcastOpUT(op_type ="reduce_log_sum" , op_module_name = "impl.reduce_log_sum", op_func_name = "reduce_log_sum")

ut_case.add_case(support_soc=["Ascend610", "Ascend310"], case={
    "params": [
        {"shape": (1,16,12,12),
         "ori_shape": (1,16,12,12),
         "format": "NCHW",
         "ori_format": "NCHW",
         "dtype": "int32" },
        {"shape": (1,12,12),
         "ori_shape": (1,12,12),
         "format": "NCHW",
         "ori_format": "NCHW",
         "dtype": "int32"},
        [],
        0,
    ]
})
ut_case.add_case(support_soc=["Ascend610", "Ascend310"], case={
    "params": [{
        "shape": (1,16,12,12),
        "ori_shape": (1,16,12,12),
        "format": "NCHW",
        "ori_format": "NCHW",
        "dtype": "float16",
    },  {
        "shape": (1,16,1,1),
        "ori_shape": (1,16,1,1),
        "format": "NCHW",
        "ori_format": "NCHW",
        "dtype": "float16"
    },
        [2,3],
        1,
    ]
})
def np_reduce_log_sum(x, y, axes, keepdims):
    '''input tensor(dict): x
       output tensor(dict): y
       attribute listint : axes
       attribute int:keepdims
    '''
    input_tensor = x.get("value")
    if keepdims == 1:
        res1 = np.sum(input_tensor, axis = tuple(axes), keepdims = True)
    elif keepdims == 0:
        res1 = np.sum(input_tensor, axis = tuple(axes), keepdims = False)
    y = np.log(res1)
    return y


ut_case.add_precision_case(support_soc=["Ascend610", "Ascend310"], case={
    "params": [{
        "shape": (1,16,12,12),
        "ori_shape": (1,16,12,12),
        "format": "NCHW",
        "ori_format": "NCHW",
        "dtype": "float16",
        "param_type": "input",
        "value_range": [0.0, 10.0]
    },  {
        "shape": (1,1,12,12),
        "ori_shape": (1,1,12,12),
        "format": "NCHW",
        "ori_format": "NCHW",
        "dtype": "float16",
        "param_type": "output"
    },
        [1],
        1,
    ],
    "case_name": "test_reduce_log_sum_precision",
    "calc_expect_func": np_reduce_log_sum,
})

