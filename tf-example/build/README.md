

```
gcc -O2     -I./codegen/host/include     -I./runtime/include     -I/path/to/tvm/include     -I/path/to/tvm/3rdparty/dlpack/include     -I/path/to/tvm/3rdparty/dmlc-core/include     main.c codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c     runtime/src/runtime/crt/common/*.c     runtime/src/runtime/crt/aot_executor/*.c     runtime/src/runtime/crt/aot_executor_module/*.c     runtime/src/runtime/crt/graph_executor/*.c     runtime/src/runtime/crt/memory/*.c     platform.c     -o run_inference -I. -lm
```