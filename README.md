# YOLOv8 推理

# 如何运行
**NOTE: OpenCV版本要求>=4.7.0，测试版本为4.7.0**
```bash
git clone https://github.com/Estellasy/yolov8-defect-cpp-inference.git
cd yolov8-defect-cpp-inference
mkdir build
cd build
cmake ..
make
./Yolov8CPPInference
```

# 目录结构
```bash
.
├── assets          # 测试图片
│   ├── crack.bmp
│   └── hole.bmp
├── benchmark.h     # 性能测试
├── CMakeLists.txt
├── draft.txt
├── inference.cpp   # 推理API
├── inference.h
├── main.cpp    
├── models          # 模型
│   └── best.onnx
├── README.md     
├── yolov8.cpp      # 推理和后处理
└── yolov8.h    
```

# 缺陷类型
目前已设置4类缺陷类型，分别为：
- 异物 object
- 裂缝 crack
- 孔洞 hole
- 褶皱 wrinkle

# 参数修改
## 路径相关
- 在`main.cpp`中修改传入测试图片路径`imagePath`和设置是否使用GPU加速`runOnGPU`。
- 在`main.cpp`中指定`imagePath`并进行推理后的保存等相关工作。
- 在`yolov8.cpp`中修改模型路径`modelPath`。

## 推理相关
- 在`inference.h`中修改`modelConfidenceThreshold`、`modelScoreThreshold`、`modelNMSThreshold`，分别对应`置信度阈值`、`分数阈值`、`NMS阈值`。

# 性能测试
**测试环境**
```bash
Intel® Core™ i5-13400, 32G RAM
```

**测试表现**
```bash
Total time for 1000 iterations: 72182 milliseconds
Average time per iteration: 72.18 milliseconds
```

CUDA上的性能测试待补充。

目前`yolov8.cpp`逻辑为：
- 加载模型
- 加载测试图片
- 推理
- 后处理

处理每一张图像都会重复加载模型，实际应用时可以**将模型加载和推理解耦**。

模型正确运行时，Console输出下列信息：
```bash
Running on CPU
Number of detections:1
```

若提示下面内容，则为未配置好CUDA环境。
```bash
Running on CUDA
[ WARN:0@0.027] global net_impl.cpp:174 setUpNet DNN module was not built with CUDA backend; switching to CPU
Number of detections:1
```
