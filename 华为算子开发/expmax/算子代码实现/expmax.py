"""
Copyright (C) 2020. Huawei Technologies Co., Ltd. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the Apache License Version 2.0.You may not use
this file except in compliance with the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
Apache License for more details at
http://www.apache.org/licenses/LICENSE-2.0

expmax
"""

import te.lang.cce
from te import tvm
from te.platform.fusion_manager import fusion_manager
from topi import generic
from topi.cce import util

SHAPE_SIZE_LIMIT = 2147483648


@fusion_manager.register("expmax")
def expmax_compute(input_x, scale):
    """
    calculating data

    Parameters
    ----------
    input_x : TVM tensor
        the placeholder of input_x
    output_y : dict
        dict of output_y, include keys(shape and dtype)
    kernel_name : str
        kernel name, default value is "expmax"

    Returns
    -------
    output tensor
    """
    dtype = input_x.dtype
    if dtype == 'float16':
        input_x = te.lang.cce.cast_to(input_x, "float32")
    x_reduce_max = te.lang.cce.reduce_max(input_x, axis=-1, keepdims=True)
    shape_x = te.lang.cce.util.shape_to_list(input_x.shape)
    shape_y = te.lang.cce.util.shape_to_list(x_reduce_max.shape)
    shape_x, shape_y, shape_max = util.produce_shapes(shape_x, shape_y)
    util.check_shape_size(shape_max, SHAPE_SIZE_LIMIT)
    input_x = te.lang.cce.broadcast(input_x, shape_max)
    x_reduce_max = te.lang.cce.broadcast(x_reduce_max, shape_max)
    x_sub = te.lang.cce.vsub(input_x, x_reduce_max)
    mul_res = te.lang.cce.vmuls(x_sub, scale)
    fina_res = te.lang.cce.vexp(mul_res)
    if dtype == 'float16':
        fina_res = te.lang.cce.cast_to(fina_res, "float16")

    return fina_res


@util.check_input_type(dict, dict, float, str)
def expmax(input_x, scale, kernel_name="expmax"):
    """
    calculating data

    Parameters
    ----------
    input_x : dict
        shape and dtype of input
    output_y : dict
        shape and dtype of output, should be same shape and type as input
    kernel_name : str
        kernel name, default value is "expmax"

    Returns
    -------
    None
    """
    shape = util.scalar2tensor_one(input_x.get("shape"))
    util.check_kernel_name(kernel_name)
    util.check_shape_rule(shape)
    util.check_tensor_shape_size(shape)

    check_tuple = ("float16", "float32")
    input_data_type = input_x.get("dtype").lower()
    util.check_dtype_rule(input_data_type, check_tuple)

    data_input = tvm.placeholder(shape, name="data_input", dtype=input_data_type)

    res = expmax_compute(data_input, scale)

    with tvm.target.cce():
        schedule = generic.auto_schedule(res)

    config = {"name": kernel_name,
              "tensor_list": [data_input, res]}

    te.lang.cce.cce_build_code(schedule, config)
