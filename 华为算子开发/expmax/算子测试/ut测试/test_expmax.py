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

expmax ut case
"""
import unittest
from impl.expmax import expmax

def expmax_cce(shape_x, dtype, scale, kernel_name="ExpMax"):
    expmax({"shape":shape_x, "dtype":dtype}, {"shape":shape_x, "dtype":dtype}, scale, kernel_name=kernel_name)

class Test_expmax_cce(unittest.TestCase):
    def tearDown(self):
        # Do this after each test case is executed.
        pass

    def setUp(self):
        # Do this before each test case is executed.
        pass

    @classmethod
    def tearDownClass(self):
        # Must use the @classmethod decorator, run once after all tests have run
        pass

    @classmethod
    def setUpClass(self):
        # Must use the @classmethod decorator, run once before all tests have run
        pass

    def test_function_case1(self):
        expmax_cce((1, 20, 20, 3), "float16", 2., "cce_ExpMax_1_float16")

    def test_function_case2(self):
        expmax_cce((5, 100, 1000, 3), "float16", 2., "cce_ExpMax_2_float16")

    def test_function_case3(self):
        expmax_cce((2, 20, 40, 3), "float16", 2., "cce_ExpMax_3_float16")

    def test_function_case4(self):
        expmax_cce((11, 22, 58, 3), "float16", 2., "cce_ExpMax_4_float16")

    def test_function_case5(self):
        expmax_cce((15, 68, 145, 3), "float16", 2., "cce_ExpMax_5_float16")

if __name__ == "__main__":
    unittest.main()
    exit(0)