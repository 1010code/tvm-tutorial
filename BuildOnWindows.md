
## TVM Windows 安裝
TVM 支援透過 MSVC 使用CMake 建置。需要有一個 Visual Studio 編譯器。 VS 的最低版本為Visual Studio Enterprise 2019。
開始工具列搜尋  Developer Command Prompt for VS 2019 開啟終端機。


### 下載 TVM
下載 TVM 的 GitHub 儲存庫。

```
git clone --recursive https://github.com/apache/tvm tvm
```


建立一個建置目錄，將cmake/config.cmake複製到該目錄。

```
cd tvm
mkdir build
copy cmake\config.cmake build\
```

建構TVM 及相關函式庫(使用Ninja 來加速構建)：

```
cd build
cmake .. -G Ninja
ninja
```