import tvm
import onnx
import skl2onnx
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType


# 導入 ONNX 模型至 TVM Relay
import tvm.relay as relay

onnx_model = onnx.load("tf_model.onnx")
shape_dict = {"float_input": (1, 4)}
mod, params = relay.frontend.from_onnx(onnx_model, shape_dict)

# 定義目標硬體平台 (這裡以 `c` 為主，代表原生 C 代碼)
target = tvm.target.target.micro("host")

# 設定編譯選項
with tvm.transform.PassContext(opt_level=0):
    lowered_module = relay.build(mod, target=target, params=params, executor=tvm.relay.backend.Executor("aot"))

# 將生成的模型保存為 C 源碼
lowered_module.get_lib().export_library("iris_model.c", tvm.micro.export_model_library_format)