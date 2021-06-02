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

accum
"""


import te.lang.cce
from te import tvm, tik
from te.platform.fusion_manager import fusion_manager
from te import platform as cce
from topi import generic
from topi.cce import util
from functools import reduce as functools_reduce
import copy
import math


class Accum():
    """
    none
    """
    def __init__(self, input_flow, input_img, kernel_name="accum"):
        self.tik_instance = tik.Tik(tik.Dprofile("v100", "cloud"))
        self.shape_flow = input_flow.get("shape")
        self.dtype_flow = input_flow.get("dtype")
        self.shape_img = input_img.get("shape")
        self.dtype_img = input_img.get("dtype")
        self.shape_output = list(copy.deepcopy(self.shape_flow))
        self.shape_output[2] = self.shape_img[2]
        self.shape_output[3] = self.shape_img[3]
        self.num_flow = functools_reduce(lambda x, y: x * y, self.shape_flow)
        self.num_output = functools_reduce(lambda x, y: x * y, self.shape_output)
        # NCWH, 1 h*w as a unit
        self.hw_size_flow = self.shape_flow[2] * self.shape_flow[3]
        self.hw_size_output = self.shape_output[2] * self.shape_output[3]
        self.nc = self.shape_flow[0] * self.shape_flow[1]
        self.kernel_name = kernel_name
        self.aicore_num = 2
        # for img, only its shape matters, so img don't have to be moved
        block_bite_size = 32
        ub_size_bytes = te.platform.get_soc_spec('UB_SIZE')
        dtype_bytes_size = cce.cce_intrin.get_bit_len(self.dtype_flow) // 8
        self.data_each_block = block_bite_size // dtype_bytes_size
        self.ub_tensor_size = (
                ub_size_bytes // dtype_bytes_size // self.data_each_block *
                self.data_each_block)
        # how many h*w can be put in ub
        self.ub_hw_num = self.ub_tensor_size // self.hw_size_flow
        self.hw_num_each_core = self.nc // self.aicore_num
        self.flow_gm = self.tik_instance.Tensor(
            self.dtype_flow, self.shape_flow, name="flow_gm", scope=tik.scope_gm)
        self.output_gm = self.tik_instance.Tensor(
            self.dtype_flow, self.shape_output, name="output_gm", scope=tik.scope_gm)

    def accum_compute(self):
        """
        none
        """
        with self.tik_instance.for_range(0, self.aicore_num, block_num=self.aicore_num) as index:
            self.flow_ub = self.tik_instance.Tensor(
                self.dtype_flow, (self.ub_tensor_size,),
                name="flow_ub",
                scope=tik.scope_ubuf)

            move_offset = index * self.hw_num_each_core

            self.accum_compute_each_core(move_offset, self.hw_num_each_core)

        self.tik_instance.BuildCCE(
            kernel_name=self.kernel_name,
            inputs=[self.flow_gm],
            outputs=[self.output_gm]
        )

        return self.tik_instance

    def accum_compute_each_core(self, move_offset, move_num):
        """
        none
        """
        loop_time = move_num // self.ub_hw_num
        core_offset = move_offset
        if loop_time > 0:
            with self.tik_instance.for_range(0, loop_time) as loop_index:
                move_offset = loop_index * self.ub_hw_num + core_offset
                self.accum_compute_each_loop(move_offset, self.ub_hw_num)
            move_offset = loop_time * self.ub_hw_num + core_offset
        last_num = move_num % self.ub_hw_num
        if last_num > 0:
            self.accum_compute_each_loop(move_offset, last_num)

    def accum_compute_each_loop(self, move_offset, move_num):
        """
        none
        """
        self.burse_len_flow = math.ceil(move_num * self.hw_size_flow / self.data_each_block)
        self.tik_instance.data_move(self.flow_ub, self.flow_gm[move_offset], 0, 1,
                                    self.burse_len_flow, 0, 0)

        accum_loop = move_num
        loop_offset = move_offset
        with self.tik_instance.for_range(0, accum_loop) as hw_index:
            move_offset = hw_index * self.hw_size_flow + loop_offset
            self.accum_compute_each_hw(move_offset)

    def accum_compute_each_hw(self, move_offset):
        """
        none
        """
        pos_idx = 0

        with self.tik_instance.for_range(0, self.hw_size_output):
            pos_h, pos_w = self.idx_o2n(self.shape_output, pos_idx)
            i = pos_h * self.shape_flow[2] / self.shape_output[2]
            j = pos_w * self.shape_flow[3] / self.shape_output[3]
            i = math.floor(i)
            j = math.floor(j)
            u = pos_h * self.shape_flow[2] / self.shape_output[2] - i
            v = pos_w * self.shape_flow[3] / self.shape_output[3] - j
            scalar_u = self.tik_instance.Scalar(dtype=self.dtype_flow, init_value=u)
            scalar_v = self.tik_instance.Scalar(dtype=self.dtype_flow, init_value=v)

            idx1 = self.idx_n2o(self.shape_flow, i, j, move_offset * self.hw_size_flow)
            idx2 = self.idx_n2o(self.shape_flow, i, j + 1, move_offset * self.hw_size_flow)
            idx3 = self.idx_n2o(self.shape_flow, i + 1, j, move_offset * self.hw_size_flow)
            idx4 = self.idx_n2o(self.shape_flow, i + 1, j + 1, move_offset * self.hw_size_flow)
            scalar_1 = self.tik_instance.Scalar(dtype=self.dtype_flow,
                                              init_value=self.flow_ub[idx1])
            scalar_2 = self.tik_instance.Scalar(dtype=self.dtype_flow,
                                              init_value=self.flow_ub[idx2])
            scalar_3 = self.tik_instance.Scalar(dtype=self.dtype_flow,
                                              init_value=self.flow_ub[idx3])
            scalar_4 = self.tik_instance.Scalar(dtype=self.dtype_flow,
                                              init_value=self.flow_ub[idx4])

            out_scalar = self.tik_instance.Scalar(dtype=self.dtype_flow,
                                                init_value=(1. - scalar_u) * (1. - scalar_v) * scalar_1 +
                                                           (1. - scalar_u) * scalar_v * scalar_2 +
                                                           scalar_u * (1 - scalar_v) * scalar_3 +
                                                           scalar_u * scalar_v * scalar_4
                                                )
            out_idx = pos_idx + move_offset * self.hw_size_output
            self.flow_ub[out_idx].set_as(out_scalar)
            pos_idx += 1
            self.tik_instance.data_move(self.output_gm[move_offset],
                                        self.flow_ub, 0, 1, self.burse_len_flow, 0, 0)

    def idx_o2n(self, shape, idx, offset=None):
        """
        none
        """
        if offset is not None:
            idx -= offset

        h = shape[2]
        pos_h = idx // h
        pos_w = idx % h

        return pos_h, pos_w

    def idx_n2o(self, shape, pos_h, pos_w, offset=None):
        """
        none
        """
        h = shape[2]
        idx = pos_h * h + pos_w

        if offset is not None:
            idx += offset

        return idx


@util.check_input_type(dict, dict, dict, str)
def accum(input_flow, input_img,output):
    """
    none
    """
    ac = Accum(input_flow, input_img, kernel_name="accum")
    ac.accum_compute()
