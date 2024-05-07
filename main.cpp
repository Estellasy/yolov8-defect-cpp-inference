#include <iostream>
#include <vector>
#include <getopt.h>

#include <opencv2/opencv.hpp>

// #include "yolov8.h"
#include "benchmark.h"

using namespace std;
using namespace cv;

int main()
{
    bool runOnGPU = false;
    // 性能测试
    // benchmarkTest(runOnGPU);
    std::string imagePath = "/media/siyi/red/hg/yolov8/yolov8-defect-cpp-inference/assets/wrinkle.bmp"; // 输入路径
    cv::Mat output = yolov8Detection(imagePath, runOnGPU);                                              // 推理

    // 提取文件名
    auto fileNameStart = imagePath.find_last_of('/') + 1;
    std::string fileName = imagePath.substr(fileNameStart);
    // 构建保存路径
    std::string savePath = "/media/siyi/red/hg/yolov8/yolov8-defect-cpp-inference/output/" + fileName;
    // 保存结果
    cv::imwrite(savePath, output);
    std::cout << "Result saved successfully at: " << savePath << std::endl;
    return 0;
}