#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <tvmgen_default.h> // 用來取得輸入/輸出結構及WORKSPACE_SIZE定義

#ifdef _WIN32
#include <windows.h>
#define LoadDynamicLibrary(path) LoadLibraryA(path)
#define GetFunctionFromLibrary(lib_ptr, func_name) GetProcAddress((HMODULE)lib_ptr, func_name)
#define FreeDynamicLibrary(lib_ptr) FreeLibrary((HMODULE)lib_ptr)
static const char DefaultLibraryPath[] = "libmodel.dll";

#elif __linux__
#include <dlfcn.h>
#define LoadDynamicLibrary(path) dlopen(path, RTLD_NOW)
#define GetFunctionFromLibrary(lib_ptr, func_name) dlsym(lib_ptr, func_name)
#define FreeDynamicLibrary(lib_ptr) dlclose(lib_ptr)
static const char DefaultLibraryPath[] = "./libmodel.so";

#else
#error "Unsupported platform"
#endif

// 定義工作空間
uint8_t workspace[TVMGEN_DEFAULT_WORKSPACE_SIZE];

// 定義函式型態，與 tvmgen_default_run 的原型相同
// tvmgen_default_run(struct tvmgen_default_inputs* inputs, struct tvmgen_default_outputs* outputs)
typedef int32_t (*tvm_run_t)(struct tvmgen_default_inputs*, struct tvmgen_default_outputs*);

int main() {
    // 載入動態函式庫
    void* lib_handle = LoadDynamicLibrary(DefaultLibraryPath);
    if (!lib_handle) {
#ifdef _WIN32
        fprintf(stderr, "Failed to load library: %s\n", DefaultLibraryPath);
#else
        fprintf(stderr, "Failed to load library: %s, error: %s\n", DefaultLibraryPath, dlerror());
#endif
        return -1;
    }

    // 取得函式指標
    tvm_run_t tvmgen_run = (tvm_run_t)GetFunctionFromLibrary(lib_handle, "tvmgen_default_run");
    if (!tvmgen_run) {
#ifdef _WIN32
        fprintf(stderr, "Failed to get function 'tvmgen_default_run'\n");
#else
        fprintf(stderr, "Failed to get function 'tvmgen_default_run', error: %s\n", dlerror());
#endif
        FreeDynamicLibrary(lib_handle);
        return -1;
    }

    // 準備輸入及輸出資料
    float input_data[4] = {6.3, 3.3, 6.0, 2.5};
    int32_t output0_data;
    float output1_data[3];

    struct tvmgen_default_inputs inputs = {
        .float_input = (void*)input_data
    };

    struct tvmgen_default_outputs outputs = {
        .output0 = (void*)&output0_data,
        .output1 = (void*)output1_data
    };

    // 呼叫 run 函式
    int32_t result = tvmgen_run(&inputs, &outputs);
    if (result != 0) {
        fprintf(stderr, "Error: tvmgen_default_run failed with code %d\n", result);
        FreeDynamicLibrary(lib_handle);
        return -1;
    }

    printf("First Inference:\n");
    printf("Output0: %d\n", output0_data);
    printf("Output1: %f %f %f\n", output1_data[0], output1_data[1], output1_data[2]);

    // 釋放動態函式庫
    FreeDynamicLibrary(lib_handle);

    return 0;
}
