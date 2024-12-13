

# 編譯與執行說明

## C(gcc)編譯

### Linux 平台編譯與執行
```
gcc -O2 \
    -I./codegen/host/include \
    -I./runtime/include \
    -I. \
    main.c codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c \
    runtime/src/runtime/crt/common/*.c \
    runtime/src/runtime/crt/aot_executor/*.c \
    runtime/src/runtime/crt/memory/*.c \
    platform.c \
    -lm \
    -o main
    
 ./main
```

## C++(g++)編譯  obj
### Linux 平台編譯與執行
在 Linux 平台下，請依以下指令完成編譯與執行：

**1. 編譯程式碼：**
```
gcc -O2 \
    -I./codegen/host/include \
    -I./runtime/include \
    -I. \
    -c codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c \
    runtime/src/runtime/crt/common/*.c \
    runtime/src/runtime/crt/aot_executor/*.c \
    runtime/src/runtime/crt/memory/*.c \
    platform.c
```

### Windows 平台編譯與執行
在 Windows 平台上，由於使用 __declspec(dllimport) 預設從動態連結庫（DLL）匯入符號，因此需要關閉 dllimport 修飾符，並啟用靜態連結。請於編譯時加入以下定義：

- -DTVM_DLL=：取消 TVM 預設的 DLL 匯入行為。
- -DTVM_CRT_STATIC_LIBRARY=1：啟用靜態連結支援。

```
gcc -O2 \
    -I./codegen/host/include \
    -I./runtime/include \
    -I. \
    main.c codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c \
    runtime/src/runtime/crt/common/*.c \
    runtime/src/runtime/crt/aot_executor/*.c \
    runtime/src/runtime/crt/memory/*.c \
    platform.c \
    -lm \
    -DTVM_DLL= \
    -DTVM_CRT_STATIC_LIBRARY=1 \
    -o main.exe
```

**2. 連結並生成執行檔：**

```
g++ -O2 *.o -lm main.cpp -I./codegen/host/include -o main -pthread
```

**3. 清除中間檔案：**

```
rm -rf *.o
```

**4. 執行產生的主程式：**

```
./main
```

### Windows 平台編譯與執行
在 Windows 平台上，由於使用 __declspec(dllimport) 預設從動態連結庫（DLL）匯入符號，因此需要關閉 dllimport 修飾符，並啟用靜態連結。請於編譯時加入以下定義：

- -DTVM_DLL=：取消 TVM 預設的 DLL 匯入行為。
- -DTVM_CRT_STATIC_LIBRARY=1：啟用靜態連結支援。

**1. 編譯程式碼：**

```
gcc -O2 -I./codegen/host/include  -I./runtime/include  -I.  -c codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c  runtime/src/runtime/crt/common/*.c  runtime/src/runtime/crt/aot_executor/*.c  runtime/src/runtime/crt/memory/*.c  platform.c -DTVM_DLL= -DTVM_CRT_STATIC_LIBRARY=1
```

**2. 連結並生成執行檔：**

```
g++ -O2 *.o -lm main.cpp -I./codegen/host/include -o main.exe -pthread
```

**3. 清除中間檔案：**

```
rm -rf *.o
```

**4. 執行產生的主程式：**

```
./main.exe
```

## C++(g++)編譯 動態連結

### Linux 平台編譯與執行

```
gcc -O2 -fPIC \
    -I./codegen/host/include \
    -I./runtime/include \
    -I. \
    codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c \
    runtime/src/runtime/crt/common/*.c \
    runtime/src/runtime/crt/aot_executor/*.c \
    runtime/src/runtime/crt/memory/*.c \
    platform.c \
    -lm \
    -shared -o libmodel.so

g++ -O2 test.cpp -o main -I./codegen/host/include
./main
```

### Windows 平台編譯與執行

```
gcc -O2 -fPIC \
    -I./codegen/host/include \
    -I./runtime/include \
    -I. \
    codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c \
    runtime/src/runtime/crt/common/*.c \
    runtime/src/runtime/crt/aot_executor/*.c \
    runtime/src/runtime/crt/memory/*.c \
    platform.c \
    -lm \
    -DTVM_DLL= -DTVM_CRT_STATIC_LIBRARY=1 \
    -shared -o libmodel.dll

g++ -O2 test.cpp -o main.exe -I./codegen/host/include
./main.exe
```