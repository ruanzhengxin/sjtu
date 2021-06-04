import te.lang.cce
from te import tvm
from te.platform.fusion_manager import fusion_manager
from topi import generic
from topi.cce import util

#@fusion_manager.register("reduce_log_sum")
def reduce_log_sum_compute(input_x, output_y, axes, keepdims = 1, kernel_name="reduce_log_sum"):
    """
    To do: Implement the operator by referring to the
           TBE Operator Development Guide.
    """
    shape_x = te.lang.cce.util.shape_to_list(input_x.shape)
    if axes == []:
        i = 0
        for i in range(len(shape_x)):
            axes.append(i)
    if keepdims == 1:
        res1 = te.lang.cce.sum(input_x, axes, keepdims=True)
    elif keepdims == 0:
        res1 = te.lang.cce.sum(input_x, axes, keepdims=False)
    res = te.lang.cce.vlog(res1, priority_flag=1)
    return res
@util.check_input_type(dict, dict, tuple, int, str)
def reduce_log_sum(input_x, output_y, axes = None, keepdims = 1, kernel_name="reduce_log_sum"):
    """
    To do: Implement the operator by referring to the
           TBE Operator Development Guide.
    """
    shape = input_x.get("shape")
    dtype = input_x.get("dtype")
    input_dtype = dtype.lower()
    util.check_shape_rule(shape)
    util.check_tensor_shape_size(shape)
    util.check_kernel_name(kernel_name)

    check_tuple = ("float16", "float", "int32", "int64", "uint32", "uint64", "double")
    util.check_dtype_rule(input_dtype, check_tuple)
    data_input = tvm.placeholder(shape, name="data_input", dtype=input_dtype)
    res = reduce_log_sum_compute(data_input, output_y, axes, keepdims, kernel_name)

    """
    TODO:
    auto schedule
    """
    with tvm.target.cce():
        schedule = generic.auto_schedule(res)

    """
    TODO:
    operator build
    """
    config = {"name": kernel_name,
              "tensor_list": [data_input, res]}

    te.lang.cce.cce_build_code(schedule, config)
'''
if __name__ == '__main__':  
    input_output_dict = {"shape": (5, 5), "dtype": "float16"}
    reduce_log_sum(input_output_dict, input_output_dict, [0], 1, kernel_name="reduce_log_sum")
'''