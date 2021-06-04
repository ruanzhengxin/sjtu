/* Copyright (C) 2020. Huawei Technologies Co., Ltd. All 
rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the Apache License Version 2.0.
 * You may not use this file except in compliance with the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Apache License for more details at
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#include "register/register.h"
#include "ge_onnx.pb.h"
#include <string>
#include <vector>
#include <iostream>



namespace domi {
Status ParseParamsReduceLogSum(const Message *op_src, ge::Operator& op_dst)
{
    const ge::onnx::NodeProto *node = reinterpret_cast<const ge::onnx::NodeProto*>(op_src);
    if (node == nullptr) {
        // OP_LOGE(op_dst.GetName().c_str(), "Dynamic cast op_src to NodeProto failed.");
        return FAILED;
    }

    vector<int64_t> axes;
    int keepdims = 1;
    bool bFindaxes = false;
    bool bFindkeepdims = false;
    for (auto attr : node->attribute()) {
        if (attr.name() == "axes") {
            bFindaxes = true;
            for (const auto val : attr.ints()) {
                axes.push_back(val);
            }
            
        }
        if (attr.name() == "keepdims") {
            bFindkeepdims = true;
           keepdims = attr.i();         
        }
    }

    if (!bFindkeepdims) {
        keepdims = 1;
    }
    if (!bFindaxes) {
            axes = {};
        }
    op_dst.SetAttr("axes", axes);
    op_dst.SetAttr("keepdims", keepdims);
    return SUCCESS;
}    
// register op info to GE
REGISTER_CUSTOM_OP("ReduceLogSum")
    .FrameworkType(ONNX)   // type: CAFFE, TENSORFLOW
    .OriginOpType("ai.onnx::11::ReduceLogSum")      // name in tf module
    .ParseParamsFn(ParseParamsReduceLogSum)
    .ImplyType(ImplyType::TVM);
}  // namespace domi
