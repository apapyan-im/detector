#pragma once
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <functional>

namespace Capture {
    class VideoCapture {
        public:
            static void capture(const std::string& url, const std::function<std::string(cv::Mat)>& onFrame);
            static void capture(const int webcamId, const std::function<std::string(cv::Mat)>& onFrame);
    };
}
