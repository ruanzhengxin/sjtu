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

class ACCUM_ST : public testing::Test {
protected:
    static void SetUpTestCase() {
        std::cout << "ACCUM_ST ST SetUp" << std::endl;
    }
    static void TearDownTestCase() {
        std::cout << "ACCUM_ST ST TearDown" << std::endl;
    }
    virtual void SetUp() {}
    virtual void TearDown() {}
};


/*
* op: accum
* input_shape: (5, 4,10,10)
* output_shape: (5, 4,20,20)
* stype: float16
* dtype: float16
*/
TEST_F(ACCUM_ST, test_accum_5_4_10_10_float16) {
    std::string op_name = "accum";
    std::string inputSizeStr = "5_4_10_10_float16";
    uint32_t inputSize = 5*4*10*10;
    //uint32_t inputBSize = 1*1;
    uint32_t outputSize = 5*4*20*20;

    const char *stubFunc =  "cce_accum_5_4_10_10_float16__kernel0";

    std::string bin_path = "./llt/ops/common/kernel_bin/accum/cce_accum_5_4_10_10_float16.o";

    std::string tilingName = "cce_accum_5_4_10_10_float16__kernel0";

    std::string inputArrAPath = "./llt/ops/common/data/accum/5_4_10_10_float16/accum_input_5_4_10_10_float16.data";
    //std::string inputArrBPath = "./llt/ops/common/data/ExpMax/1_1_float16/ExpMax_input2_1_1_float16.data";

    std::string expectOutputDataPath = "./llt/ops/common/data/accum/5_4_10_10_float16"\
    "/accum_output_5_4_20_20_float16.data";
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
        "./llt/ops/common/data/accum/5_4_10_10_float16/actual_accum_output_5_4_20_20_float16.data",
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
TEST_F(ACCUM_ST, test_accum_2_5_5_5_float16) {
    std::string op_name = "accum";
    std::string inputSizeStr = "2_5_5_5_float16";
    uint32_t inputSize = 2*5*5*5;
    //uint32_t inputBSize = 16*32;
    uint32_t outputSize = 2*5*10*5;

    const char *stubFunc =  "cce_accum_2_5_5_5_float16__kernel0";

    std::string bin_path = "./llt/ops/common/kernel_bin/accum/cce_accum_2_5_5_5_float16.o";

    std::string tilingName = "cce_accum_2_5_5_5_float16__kernel0";

    std::string inputArrAPath = "./llt/ops/common/data/accum/2_5_5_5_float16/accum_input_2_5_5_5_float16.data";
    //std::string inputArrBPath = "./llt/ops/common/data/ExpMax/16_32_float16/ExpMax_input2_16_32_float16.data";

    std::string expectOutputDataPath = "./llt/ops/common/data/accum/2_5_5_5_float16"\
    "/accum_output_2_5_10_5_float16.data";
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
        "./llt/ops/common/data/accum/2_5_5_5_float16/actual_accum_output_2_5_10_5_float16.data",
        outputSize * sizeof(fp16_t));
    }

    assert(true == ret);
}



//11111111111111111111111111111111

TEST_F(ACCUM_ST, test_accum_6_10_10_15_float32) {
    std::string op_name = "accum";
    std::string inputSizeStr = "6_10_10_15_float32";
    uint32_t inputSize = 6*10*10*15;
    //uint32_t inputBSize = 1*1;
    uint32_t outputSize = 6*10*20*30;

    const char *stubFunc =  "cce_accum_6_10_10_15_float32__kernel0";

    std::string bin_path = "./llt/ops/common/kernel_bin/accum/cce_accum_6_10_10_15_float32.o";

    std::string tilingName = "cce_accum_6_10_10_15_float32__kernel0";

    std::string inputArrPath = "./llt/ops/common/data/accum/6_10_10_15_float32/accum_input_6_10_10_15_float32.data";
    //std::string inputArrBPath = "./llt/ops/common/data/ExpMax/1_1_float16/ExpMax_input2_1_1_float16.data";

    std::string expectOutputDataPath = "./llt/ops/common/data/accum/6_10_10_15_float32"\
    "/accum_output_6_10_20_30_float32.data";
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
        "./llt/ops/common/data/accum/6_10_10_15_float32/actual_accum_output_6_10_20_30_float32.data",
        outputSize * sizeof(float));
    }

    assert(true == ret);
}


