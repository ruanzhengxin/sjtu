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

accum ut case
"""
import unittest
from impl.accum import accum

def accum_cce(shape_x, shape_y, dtype, kernel_name='accum'):
    shape_z=(shape_x[0], shape_x[1], shape_y[2],shape_y[3])
    accum({"shape":shape_x, "dtype":dtype},{"shape":shape_y, "dtype":dtype}, {"shape":shape_z, "dtype":dtype},
          kernel_name=kernel_name)
class Test_accum_cce(unittest.TestCase):
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
        accum_cce((8,8,8,8),(1,8,4,4),"float32",
                  "cce_accum_case1")

if __name__ == "__main__":
    unittest.main()
    exit(0)