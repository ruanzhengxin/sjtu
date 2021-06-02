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

#include "expmax.h"
#include <string>
#include <vector>

namespace ge {
    bool InferShapeAndTypeExpmax(Operator& op, const string& input_name1, const string& output_name)
    {  TensorDesc vOutputDesc = op.GetOutputDesc(output_name);
        DataType input_dtype = op.GetInputDesc(input_name1).GetDataType();
        Format input_format = op.GetInputDesc(input_name1).GetFormat();
        ge::Shape shapeX = op.GetInputDesc(input_name1).GetShape();
        std::vector<int64_t> dimsX = shapeX.GetDims();
        std::vector<int64_t> dimVec;
        for(size_t i = 0; i < dimsX.size(); i++) {
            int64_t dims = dimsX[i];
            dimVec.push_back(dims);
        }
        ge::Shape outputShape = ge::Shape(dimVec);

        vOutputDesc.SetShape(outputShape);
        vOutputDesc.SetDataType(input_dtype);
        vOutputDesc.SetFormat(input_format);
        op.UpdateOutputDesc(output_name, vOutputDesc);

        return true;

    }

    //---------
    IMPLEMT_VERIFIER(Expmax, ExpmaxVerify)
    {
        return GRAPH_SUCCESS;
    }

    // Obtains the processing function of the output tensor description.
    IMPLEMT_COMMON_INFERFUNC(ExpmaxInferShape)
    {
        if(InferShapeAndTypeExpmax(op, "input_x", "output_y")) {
            return GRAPH_SUCCESS;
        }
        return GRAPH_FAILED;
    }

    //Registered inferfunction
    COMMON_INFER_FUNC_REG(Expmax, ExpmaxInferShape);

    //Registered verify function
    VERIFY_FUNC_REG(Expmax,ExpmaxVerify);
}  // namespace ge
