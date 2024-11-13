
## TVM Linux 安裝

### 安裝必要的工具和庫

Apache TVM 需要以下相依性：
- CMake (>= 3.24.0)
- LLVM（建議 >= 15）
- git
- C++ 編譯器至少支援 C++ 17
    - GCC 7.1
    - Clang 5.0
    - Apple Clang 9.3
    - Visual Studio 2019 (v16.7)
- Python (>= 3.8)
- 建議使用 Conda 建立 Python 環境


若 cmake 編譯出現以下錯誤訊息，則需要安裝:

> Could NOT find ZLIB (missing: ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

```
sudo apt-get update
sudo apt-get install zlib1g-dev
```

管理依賴關係最簡單的方法是透過 conda，它維護一組跨平台的工具鏈，包括 LLVM。要建立這些建置依賴項的環境，輸入以下指令建立一個新的環境：

```
# make sure to start with a fresh environment
conda env remove -n tvm-build-venv
# create the conda environment with build dependency
conda create -n tvm-build-venv -c conda-forge \
    "llvmdev>=15" \
    "cmake>=3.24" \
    git \
    python=3.11
# enter the build environment
conda activate tvm-build-venv
```


### 下載 TVM
下載 TVM 的 GitHub 儲存庫。

```
git clone --recursive https://github.com/apache/tvm tvm
```


建立一個建置目錄，將cmake/config.cmake複製到該目錄。

```
cd tvm
rm -rf build && mkdir build && cd build
# Specify the build configuration via CMake options
cp ../cmake/config.cmake .
```

修改 cmake 編譯的設定參數，可依據需求 ON/OFF。

```
# controls default compilation flags (Candidates: Release, Debug, RelWithDebInfo)
echo "set(CMAKE_BUILD_TYPE RelWithDebInfo)" >> config.cmake

# LLVM is a must dependency for compiler end
echo "set(USE_LLVM \"llvm-config --ignore-libllvm --link-static\")" >> config.cmake
echo "set(HIDE_PRIVATE_SYMBOLS ON)" >> config.cmake

# GPU SDKs, turn on if needed
echo "set(USE_CUDA   OFF)" >> config.cmake
echo "set(USE_METAL  OFF)" >> config.cmake
echo "set(USE_VULKAN OFF)" >> config.cmake
echo "set(USE_OPENCL OFF)" >> config.cmake

# cuBLAS, cuDNN, cutlass support, turn on if needed
echo "set(USE_CUBLAS OFF)" >> config.cmake
echo "set(USE_CUDNN  OFF)" >> config.cmake
echo "set(USE_CUTLASS OFF)" >> config.cmake

echo "set(USE_MICRO ON)" >> config.cmake
```

設定好 config.cmake 之後，使用以下命令啟動建置：


```
cmake .. && cmake --build . --parallel $(nproc)
```



亦可使用Ninja 來加速構建(與上指令兩者選一編譯即可)：

```
cmake .. -G Ninja && ninja
```

成功編譯後應該在 build 目錄下會看到 `libtvm.so` 和 `libtvm_runtime.so`。


可以將編譯好的共享庫班一道系統路徑。
```sh
sudo cp build/*.so /usr/local/lib/
```


### 安裝Python套件(省略)

```
cd ../python
python setup.py install --user
```

使用以下指令尋找是否有 runtime
```
ldconfig -p | grep libtvm_runtime
```
通常我們會將runtime系統路徑下，如果將runtime放置自己的資料夾可以輸入以下指令。

```
export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH

# 亦或是將 so 放到 /usr/local/lib/
sudo ldconfig 
```

編譯指令

```
g++ -std=c++17 -o main test.cpp     -I../tvm/include     -I../tvm/3rdparty/dlpack/include     -I../tvm/3rdparty/dmlc-core/include     ../tvm/build/libtvm_runtime.so     -ldl -pthread
```


## Reference
- [TVM 從原始碼安裝流程](https://tvm.hyper.ai/docs/install/from_source)
- [TVM Install from Source](https://tvm.apache.org/docs/install/from_source.html)
- [提到安裝LLVM ON](https://blog.csdn.net/justsolow/article/details/107371838)