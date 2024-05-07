#include "yolov8.h"

cv::Mat yolov8Detection(std::string imagePath, bool runOnGPU)
{
    std::string modelPath = "/media/siyi/red/hg/yolov8/yolov8-defect-cpp-inference/models/best.onnx";

    // 导出的onnx模型只能接收640x640大小的输入，在这里需要进行缩放，否则会出现检测失败
    Inference inf(modelPath, cv::Size(640, 640), "", runOnGPU);

    cv::Mat frame = cv::imread(imagePath);
    // Resize image to 640x640
    cv::Mat resizedFrame;
    cv::resize(frame, resizedFrame, cv::Size(640, 640));

    // Inference starts here...
    // 开始推理
    std::vector<Detection> output = inf.runInference(resizedFrame);

    // 对输出进行后处理和边界框绘制
    int detections = output.size(); // 检测出了多少缺陷
    std::cout << "Number of detections:" << detections << std::endl;

    for (int i = 0; i < detections; ++i) // 边界框绘制
    {
        Detection detection = output[i];

        cv::Rect box = detection.box;

        // Scale detection box coordinates back to original image size
        box.x = box.x * frame.cols / 640;
        box.y = box.y * frame.rows / 640;
        box.width = box.width * frame.cols / 640;
        box.height = box.height * frame.rows / 640;

        cv::Scalar color = detection.color;

        // Detection box
        cv::rectangle(frame, box, color, 2);

        // Detection box text
        std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
        cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
        cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

        cv::rectangle(frame, textBox, color, cv::FILLED);
        cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
    }
    // Inference ends here...

    // This is only for preview purposes
    float scale = 0.8;
    cv::resize(frame, frame, cv::Size(frame.cols * scale, frame.rows * scale));
    return frame; // 返回frame
    // cv::imshow("Inference", frame);
}