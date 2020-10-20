#include "VideoCapture.h"


#include <opencv2/opencv.hpp>
#include <functional>
#include <unistd.h>

void captureVideo(cv::VideoCapture from, const std::function<void(cv::Mat)>& onFrame) {
    if (!from.isOpened()) {
        exit(1);
    }
    cv::Mat frame;
    while(true) {
        from >> frame;
        if (frame.empty()){
            unsigned int microseconds = 1000;
            usleep(microseconds);
            continue;
        }
        onFrame(frame);
    }
}


void Capture::VideoCapture::capture(const std::string& url, const std::function<void(cv::Mat)>& onFrame){
    cv::VideoCapture stream(url);
    captureVideo(stream, onFrame);
}

void Capture::VideoCapture::capture(const int webcamId, const std::function<void(cv::Mat)>& onFrame){
    cv::VideoCapture webcam(webcamId);
    captureVideo(webcam, onFrame);
}