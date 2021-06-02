/* Copyright (C) 2020. Huawei Technologies Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Apache License Version 2.0.You may not use
 * this file except in compliance with the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Apache License for more details at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "gtest/gtest.h"
#include "one_in_one_out_layer.hpp"

class Expmax_ST : public testing::Test {
protected:
    static void SetUpTestCase() {
        std::cout << "EXPMAX_ST ST SetUp" << std::endl;
    }
    static void TearDownTestCase() {
        std::cout << "EXPMAX_ST ST TearDown" << std::endl;
    }
    virtual void SetUp() {}
    virtual void TearDown() {}
};


/*
* op: expmax
* input_shape: (1, 10,10,4)
* output_shape: (1, 10,10,4)
* stype: float16
* dtype: float16
*/
TEST_F(Expmax_ST, test_expmax_5_10_10_4_float16) {
    std::string op_name = "expmax";
    std::string inputSizeStr = "5_10_10_4_float16";
    uint32_t inputSize = 5*10*10*4;
    //uint32_t inputBSize = 1*1;
    uint32_t outputSize = 5*10*10*4;

    const char *stubFunc =  "cce_expmax_5_10_10_4_float16__kernel0";

    std::string bin_path = "./llt/ops/common/kernel_bin/expmax/cce_expmax_5_10_10_4_float16.o";

    std::string tilingName = "cce_expmax_5_10_10_4_float16__kernel0";

    std::string inputArrAPath = "./llt/ops/common/data/expmax/5_10_10_4_float16/expmax_input_5_10_10_4_float16.data";
    //std::string inputArrBPath = "./llt/ops/common/data/ExpMax/1_1_float16/ExpMax_input2_1_1_float16.data";

    std::string expectOutputDataPath = "./llt/ops/common/data/expmax/5_10_10_4_float16"\
    "/expmax_output_5_10_10_4_float16.data";
    float ratios[2] = {0.001 ,0.001};

    OneInOneOutLayer<fp16_t,fp16_t> layer{
        op_name,
        inputSizeStr,
        inputSize,
        //inputBSize,
        outputSize,
        bin_path,
        tilingName,
        inputArrAPath,
        //inputArrBPath,
        expectOutputDataPath,
        ratios,
        (void*)stubFunc
    };

    bool ret = layer.test();

    if(!ret)
    {
        layer.writeBinaryFile((void*)layer.outputData,
        "./llt/ops/common/data/expmax/5_10_10_4_float16/actual_expmax_output_5_10_10_4_float16.data",
        outputSize * sizeof(fp16_t));
    }

    assert(true == ret);
}

/*
* op: add
* input_shape: (16, 32,32,5)
* output_shape: (16, 32,32,5)
* stype: float16
* dtype: float16
*/
TEST_F(Expmax_ST, test_expmax_2_5_5_5_float16) {
    std::string op_name = "expmax";
    std::string inputSizeStr = "2_5_5_5_float16";
    uint32_t inputSize = 2*5*5*5;
    //uint32_t inputBSize = 16*32;
    uint32_t outputSize = 2*5*5*5;

    const char *stubFunc =  "cce_expmax_2_5_5_5_float16__kernel0";

    std::string bin_path = "./llt/ops/common/kernel_bin/expmax/cce_expmax_2_5_5_5_float16.o";

    std::string tilingName = "cce_expmax_2_5_5_5_float16__kernel0";

    std::string inputArrAPath = "./llt/ops/common/data/expmax/2_5_5_5_float16/expmax_input_2_5_5_5_float16.data";
    //std::string inputArrBPath = "./llt/ops/common/data/ExpMax/16_32_float16/ExpMax_input2_16_32_float16.data";

    std::string expectOutputDataPath = "./llt/ops/common/data/expmax/2_5_5_5_float16"\
    "/expmax_output_2_5_5_5_float16.data";
    float ratios[2] = {0.001 ,0.001};

    OneInOneOutLayer<fp16_t,fp16_t> layer{
        op_name,
        inputSizeStr,
        inputSize,
        //inputBSize,
        outputSize,
        bin_path,
        tilingName,
        inputArrAPath,
        //inputArrBPath,
        expectOutputDataPath,
        ratios,
        (void*)stubFunc
    };

    bool ret = layer.test();

    if(!ret)
    {
        layer.writeBinaryFile((void*)layer.outputData,
        "./llt/ops/common/data/expmax/2_5_5_5_float16/actual_expmax_output_2_5_5_5_float16.data",
        outputSize * sizeof(fp16_t));
    }

    assert(true == ret);
}



//11111111111111111111111111111111

TEST_F(Expmax_ST, test_expmax_6_10_10_15_float32) {
    std::string op_name = "expmax";
    std::string inputSizeStr = "6_10_10_15_float32";
    uint32_t inputSize = 6*10*10*15;
    //uint32_t inputBSize = 1*1;
    uint32_t outputSize = 6*10*10*15;

    const char *stubFunc =  "cce_expmax_6_10_10_15_float32__kernel0";

    std::string bin_path = "./llt/ops/common/kernel_bin/expmax/cce_expmax_6_10_10_15_float32.o";

    std::string tilingName = "cce_expmax_6_10_10_15_float32__kernel0";

    std::string inputArrPath = "./llt/ops/common/data/expmax/6_10_10_15_float32/expmax_input_6_10_10_15_float32.data";
    //std::string inputArrBPath = "./llt/ops/common/data/ExpMax/1_1_float16/ExpMax_input2_1_1_float16.data";

    std::string expectOutputDataPath = "./llt/ops/common/data/expmax/6_10_10_15_float32"\
    "/expmax_output_6_10_10_15_float32.data";
    float ratios[2] = {0.0001 ,0.0001};

    OneInOneOutLayer<float,float> layer{
        op_name,
        inputSizeStr,
        inputSize,
        //inputBSize,
        outputSize,
        bin_path,
        tilingName,
        inputArrPath,
        //inputArrBPath,
        expectOutputDataPath,
        ratios,
        (void*)stubFunc
    };

    bool ret = layer.test();

    if(!ret)
    {
        layer.writeBinaryFile((void*)layer.outputData,
        "./llt/ops/common/data/expmax/6_10_10_15_float32/actual_expmax_output_6_10_10_15_float32.data",
        outputSize * sizeof(float));
    }

    assert(true == ret);
}


