#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tvmgen_default.h>
#include <iostream>
#include <chrono>  // 用於時間測量

// 定義工作空間
uint8_t workspace[TVMGEN_DEFAULT_WORKSPACE_SIZE];

int main() {
    // 初始化輸入和輸出資料
    float input_data[4] = {6.3, 3.3, 6. , 2.5};  // 假設輸入資料
    int32_t output0_data;  // 第一個輸出
    float output1_data[3];  // 第二個輸出


    // 開始計算3000次推論的總時間
    const int num_runs = 3000;
    double total_time_ms = 0.0;
    int32_t result = 0;
    for (int i = 0; i < num_runs; ++i) {
        // 計算每次推論的開始時間
        auto start_time = std::chrono::high_resolution_clock::now();

        // 配置輸入結構
        struct tvmgen_default_inputs inputs = {
            .float_input = (void*)input_data
        };

        // 配置輸出結構
        struct tvmgen_default_outputs outputs = {
            .output0 = (void*)&output0_data,
            .output1 = (void*)output1_data
        };
        // 執行推理一次
        result = tvmgen_default_run(&inputs, &outputs);
        
        // 計算推論結束時間
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        // 累積每次推論時間，轉換為毫秒
        total_time_ms += duration.count() * 1000;
    }

    // 計算平均推論時間
    double avg_time_ms = total_time_ms / num_runs;
    std::cout << "Average inference time for " << num_runs << " runs: " 
              << avg_time_ms << " ms" << std::endl;

    // int32_t result = tvmgen_default_run(&inputs, &outputs);
    if (result != 0) {
        fprintf(stderr, "Error: tvmgen_default_run failed with code %d\n", result);
        return -1;
    }

    // 打印輸出結果
    printf("Output0 (標籤): %d\n", output0_data);

    printf("Output1: ");
    for (int i = 0; i < 3; ++i) {
        printf("%f ", output1_data[i]);
    }
    printf("\n");

    return 0;
}

