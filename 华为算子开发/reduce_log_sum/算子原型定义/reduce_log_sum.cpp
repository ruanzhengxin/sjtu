#include "reduce_log_sum.h"
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
namespace ge {

    IMPLEMT_VERIFIER(ReduceLogSum, ReduceLogSumVerify)
    {
        return GRAPH_SUCCESS;
    }
    IMPLEMT_INFERFUNC(ReduceLogSum, ReduceLogSumInferShape) {
        auto tensordesc = op.GetInputDesc("input_x");
        auto shape = tensordesc.GetShape();
        std::vector<int64_t> shapeVector = shape.GetDims();
        int64_t dimNum = shape.GetDimNum();
        DataType input_type = tensordesc.GetDataType();
        std::vector<int64_t> axes = op.get_attr_axes();
        int64_t keepdims = op.get_attr_keepdims();

        if(axes.size()==0){
            for(size_t i = 0; i < shapeVector.size(); ++i)
            {
                axes.push_back(i);
            }
        }

        for(size_t i = 0; i < axes.size(); ++i)
        {
            if (axes[i] < 0){
                axes[i] = dimNum + axes[i];
            }
        }

        std::vector<int64_t> OutputShapeVector;
        std::vector<int64_t>::iterator tmp;
        for(int64_t item = 0; item < dimNum; ++item){
            tmp = std::find(axes.begin(), axes.end(), item);
            if(tmp != axes.end()){
                if(keepdims == 1){
                    OutputShapeVector.push_back(1);
                }
            }else{
                OutputShapeVector.push_back(shapeVector[item]);
            }
        }
        Shape OutputShape(OutputShapeVector);

        TensorDesc y_desc = op.GetOutputDesc("output_y");
        y_desc.SetShape(OutputShape);
        y_desc.SetDataType(input_type);
        (void)op.UpdateOutputDesc("output_y", y_desc);
        return GRAPH_SUCCESS;
    }
    INFER_FUNC_REG(ReduceLogSum, ReduceLogSumInferShape);
    VERIFY_FUNC_REG(ReduceLogSum, ReduceLogSumVerify);
}  // namespace ge
