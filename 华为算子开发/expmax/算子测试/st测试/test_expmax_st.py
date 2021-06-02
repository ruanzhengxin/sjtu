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

test expmax
"""

import unittest
import os
import shutil
from impl.expmax import expmax
from run_testcase import run_testcase, get_path_val, print_func_name

testcases = {
    "op_name": "expmax",
    "all": {"test_st_expmax_1": ((5, 10, 10, 4), "float16",  3., "cce_expmax_5_10_10_4_float16"),
            "test_st_expmax_2": ((2, 5, 5, 5), "float16", 4., "cce_expmax_2_5_5_5_float16"),
            "test_st_expmax_3": ((6, 10, 10, 15), "float32", 1., "cce_expmax_6_10_10_15_float32"),},
}

bin_path_val = get_path_val(testcases)


def test_expmax(shape_val, dtype_val, scale, kernel_name_val):
    expmax({"shape": shape_val, "dtype": dtype_val}, {"shape": shape_val, "dtype": dtype_val}, scale, kernel_name=kernel_name_val)
    kernel_meta_path = "./kernel_meta/"
    lib_kernel_name = "lib" + kernel_name_val + ".so"
    if (os.path.isfile(kernel_meta_path + lib_kernel_name)):
        shutil.move(kernel_meta_path + lib_kernel_name, bin_path_val + "/" + lib_kernel_name)
    else:
        shutil.move(kernel_meta_path + kernel_name_val + ".o", bin_path_val + "/" + kernel_name_val + ".o")
        shutil.move(kernel_meta_path + kernel_name_val + ".json", bin_path_val + "/" + kernel_name_val + ".json")


class Test_expmax_cce(unittest.TestCase):
    def tearDown(self):
        pass

    def setUp(self):
        pass

    @classmethod
    def tearDownClass(self):
        pass

    @classmethod
    def setUpClass(self):
        pass

    @print_func_name
    def test_cce_expmax(self):
        run_testcase(testcases, test_expmax)


if __name__ == "__main__":
    unittest.main()
