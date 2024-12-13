## 使用 TVM 進行模型編譯和優化
將 scikit-learn 模型轉換為輕量級的 C 程式庫而不依賴 ONNX Runtime，可以使用 TVM 來精簡所需的庫或編譯過程。TVM 將模型轉換為更小的 C/C++ 程式碼，適合嵌入式應用並支援 scikit-learn 模型。

- Apache TVM 是一個開源的機器學習編譯框架，專門設計來編譯和優化模型，並生成針對不同硬體平台的高效程式碼。TVM 支援多種深度學習框架和 ONNX 格式。
- 通過 TVM，您可以將 ONNX 模型轉換為精簡的 C/C++ 程式碼，並針對目標硬體進行優化。TVM 支援靜態編譯，因此可以生成無需額外依賴的輕量程式碼。

為了生成可跨平台執行的 C 原始碼並通過 C 進行推理，我們可以採取以下更可靠的方式：

- 使用 Hummingbird 將模型轉換為 ONNX 格式。
- 使用 TVM 將 ONNX 模型導入並編譯為 C 代碼。
- 編寫 C 程式載入並調用編譯後的模型進行推理。

## 安裝 TVM
使用 pip 安裝 TVM。請在終端機中執行以下命令：

```sh
pip install apache-tvm
```



## Reference
- [TVM Runtime 系统介紹 講解優勢](https://tvm.hyper.ai/docs/arch/arch/runtimes/)
- [TVM學習(1)--建構環境 介紹到共享庫](https://sunicyosen.github.io/2019/08/02/TVM-Study-1-Setup-Environment)
- [How to convert a network to GCC compilable C/C++ code? 提到BYOC](https://discuss.tvm.apache.org/t/how-to-convert-a-network-to-gcc-compilable-c-c-code/7846/6)
- [microTVM：裸机上的 TVM](https://tvm.hyper.ai/docs/topic/microtvm/)
- [microTVM 設計文檔](https://tvm.hyper.ai/docs/arch/arch/microtvm_design)
- [TVM从零开始学深度学习编译器](http://giantpandacv.com/project/部署优化/深度学习编译器/【从零开始学深度学习编译器】一，深度学习编译器及TVM介绍/)
- [TVM等神經編譯器概覽：它是連接深度學習框架和硬體的橋樑](https://posts.careerengine.us/p/6050781ceee8dc2d4b00faca)

