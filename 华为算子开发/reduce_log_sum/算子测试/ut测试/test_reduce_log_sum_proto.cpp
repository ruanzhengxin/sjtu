#include <gtest/gtest.h>
#include <vector>
#include "reduce_log_sum.h"

class ReduceLogSumTest : public testing::Test {
protected:
    static void SetUpTestCase() {
        std::cout << "reduce_log_sum test SetUp" << std::endl;
}

    static void TearDownTestCase() {
        std::cout << "reduce_log_sum test TearDown" << std::endl;
    }
};

TEST_F(ReduceLogSumTest, reduce_log_sum_test_case_1) {
    // [TODO] define your op here
     ge::op::ReduceLogSum reduce_log_sum_op;
     ge::TensorDesc tensorDesc;
     ge::Shape shape({1,16,12,12});
     tensorDesc.SetDataType(ge::DT_FLOAT16);
     tensorDesc.SetShape(shape);

    // [TODO] update op input here
    reduce_log_sum_op.UpdateInputDesc("input_x", tensorDesc);
    std::vector<int64_t> axes(2);
    axes.push_back(2);
    axes.push_back(3);
    reduce_log_sum_op.SetAttr("axes", axes);
    reduce_log_sum_op.SetAttr("keepdims", 1);
    // [TODO] call InferShapeAndType function here
     auto ret = reduce_log_sum_op.InferShapeAndType();
    EXPECT_EQ(ret, ge::GRAPH_SUCCESS);

    // [TODO] compare dtype and shape of op output
    auto output_desc = reduce_log_sum_op.GetOutputDesc("output_y");
    EXPECT_EQ(output_desc.GetDataType(), ge::DT_FLOAT16);
    std::vector<int64_t> expected_output_shape = {1,16,1,1};
    EXPECT_EQ(output_desc.GetShape().GetDims(), expected_output_shape);
}
