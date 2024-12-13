
gcc -O2 \
    -I./codegen/host/include \
    -I./runtime/include \
    -I. \
    -c codegen/host/src/default_lib0.c codegen/host/src/default_lib1.c \
    runtime/src/runtime/crt/common/*.c \
    runtime/src/runtime/crt/aot_executor/*.c \
    runtime/src/runtime/crt/memory/*.c \
    platform.c
    
    
g++ -O2 *.o -lm main.cpp -I./codegen/host/include -o main -pthread