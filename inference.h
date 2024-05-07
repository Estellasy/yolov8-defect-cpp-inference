#ifndef INFERENCE_H
#define INFERENCE_H

// Cpp native
#include <fstream>
#include <vector>
#include <string>
#include <random>

// OpenCV / DNN / Inference
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

struct Detection
{
    int class_id{0};         // 类别ID
    std::string className{}; // 类别名称
    float confidence{0.0};   // 置信度
    cv::Scalar color{};      // 颜色
    cv::Rect box{};          // 边界框
};

class Inference
{
public:
    Inference(const std::string &onnxModelPath, const cv::Size &modelInputShape = {640, 640}, const std::string &classesTxtFile = "", const bool &runWithCuda = true);
    std::vector<Detection> runInference(const cv::Mat &input);

private:
    void loadClassesFromFile();
    void loadOnnxNetwork();
    cv::Mat formatToSquare(const cv::Mat &source);

    std::string modelPath{};   // ONNX模型路径
    std::string classesPath{}; // 类别文件路径
    bool cudaEnabled{};        // 是否启用CUDA加速

    std::vector<std::string> classes{"object", "crack", "hole", "wrinkle"};

    cv::Size2f modelShape{};

    float modelConfidenceThreshold{0.25}; // 置信度阈值
    float modelScoreThreshold{0.45};      // 分数阈值
    float modelNMSThreshold{0.50};        // NMS阈值

    bool letterBoxForSquare = true;

    cv::dnn::Net net;
};

#endif // INFERENCE_H
