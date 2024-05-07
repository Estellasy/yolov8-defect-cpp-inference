#include <iostream>
#include <chrono>  // For timing
#include <iomanip> // For setprecision
#include <string>

#include "yolov8.h"


void benchmarkTest(bool runOnGPU)
{
    std::string imagePath = "/media/siyi/red/hg/yolov8/YOLOv8-CPP-Inference/assets/crack.bmp";

    // Number of iterations for benchmark
    int iterations = 1000;

    // Timing loop
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        yolov8Detection(imagePath, runOnGPU);
    }
    auto end = std::chrono::steady_clock::now();

    // Calculate average time per iteration
    auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    double averageTime = static_cast<double>(totalTime) / iterations;

    std::cout << "Total time for " << iterations << " iterations: " << totalTime << " milliseconds" << std::endl;
    std::cout << "Average time per iteration: " << std::fixed << std::setprecision(2) << averageTime << " milliseconds" << std::endl;
}
