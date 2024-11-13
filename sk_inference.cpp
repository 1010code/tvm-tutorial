#include <iostream>
#include <tvm/runtime/module.h>
#include <tvm/runtime/registry.h>
#include <tvm/runtime/packed_func.h>
#include <dlpack/dlpack.h>

// 定義輸入資料
float input_data[4] = {6.3, 3.3, 6.0, 2.5};

int main() {
    // 載入共享庫
    tvm::runtime::Module mod_factory = tvm::runtime::Module::LoadFromFile("./output.so");

    // 創建執行器（executor）
    DLDevice dev{kDLCPU, 0};
    tvm::runtime::Module gmod = mod_factory.GetFunction("default")(dev);
    tvm::runtime::PackedFunc set_input = gmod.GetFunction("set_input");
    tvm::runtime::PackedFunc run = gmod.GetFunction("run");
    tvm::runtime::PackedFunc get_output = gmod.GetFunction("get_output");

    // 準備 DLTensor 格式的輸入資料
    DLTensor* input;
    int64_t shape[2] = {1, 4};  // 輸入形狀
    TVMArrayAlloc(shape, 2, kDLFloat, 32, 1, kDLCPU, 0, &input);
    memcpy(input->data, input_data, sizeof(input_data));

    // // 設定模型的輸入
    set_input("float_input", input);

    // 執行推理
    run();

    // 取得第一個輸出（標籤）
    DLTensor* output_label;
    int64_t label_shape[1] = {1};  // 第一個輸出形狀
    TVMArrayAlloc(label_shape, 1, kDLInt, 64, 1, kDLCPU, 0, &output_label);
    get_output(0, output_label);

    // 打印標籤結果
    int64_t* label_data = static_cast<int64_t*>(output_label->data);
    std::cout << "Prediction Label: " << label_data[0] << std::endl;

    // 取得第二個輸出（機率值）
    DLTensor* output_prob;
    int64_t prob_shape[2] = {1, 3};  // 第二個輸出形狀 (1, 3)
    TVMArrayAlloc(prob_shape, 2, kDLFloat, 32, 1, kDLCPU, 0, &output_prob);
    get_output(1, output_prob);

    // 打印機率值
    float* prob_data = static_cast<float*>(output_prob->data);
    std::cout << "Prediction Probabilities: [";
    for (int i = 0; i < 3; ++i) {
        std::cout << prob_data[i];
        if (i < 2) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // 釋放記憶體
    TVMArrayFree(input);
    TVMArrayFree(output_label);
    TVMArrayFree(output_prob);

    return 0;
}