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

#include "accum.h"
#include <string>
#include <vector>
namespace ge {
    bool InferShapeAndTypeAccum(Operator& op, const string& input_name1, const string& input_name2,const string& output_name)
    {
    TensorDesc vOutputDesc = op.GetOutputDesc(output_name);
    DataType input_dtype = op.GetInputDesc(input_name1).GetDataType();
    Format input_format = op.GetInputDesc(input_name1).GetFormat();
    ge::Shape shapeY = op.GetInputDesc(input_name2).GetShape();
    std::vector<int64_t> dimsY = shapeY.GetDims();
    std::vector<int64_t> dimVec;
    for(size_t i = 0; i < dimsX.size(); i++) {
            int64_t dims = dimsY[i];
            dimVec.push_back(dims);
        }
    ge::Shape outputShape = ge::Shape(dimVec);
    vOutputDesc.SetShape(outputShape);
    vOutputDesc.SetDataType(input_dtype);
    vOutputDesc.SetFormat(input_format);
    op.UpdateOutputDesc(output_name, vOutputDesc);

    return true;

}

    IMPLEMT_VERIFIER(Accum, AccumVerify)
    {

        return GRAPH_SUCCESS;
    }

    // Obtains the processing function of the output tensor description.
    IMPLEMT_COMMON_INFERFUNC(AccumInferShape)
    {
        if(InferShapeAndTypeAccum(op, "input_x", "input_y", "output_z")) {
            return GRAPH_SUCCESS;
        }
        return GRAPH_FAILED;
    }

    //Registered inferfunction
    COMMON_INFER_FUNC_REG(Accum, AccumInferShape);

    //Registered verify function
    VERIFY_FUNC_REG(Accum, AccumVerify);
}  // namespace ge
