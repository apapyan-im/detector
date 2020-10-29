#include "VideoCapture.h"


#include <opencv2/opencv.hpp>
#include <functional>

void captureVideo(cv::VideoCapture from, const std::function<std::string(cv::Mat)>& onFrame) {
    if (!from.isOpened()) {
        exit(1);
    }
    cv::Mat frame;
    while(true) {
        from >> frame;
        if (frame.empty()){
            break;
        }
        onFrame(frame);
    }
}

void readDirectory(const std::string& src, const std::function<std::string(cv::Mat)>& onFrame){
    std::vector<cv::String> fileNames;
    cv::glob(src + "*.jpg", fileNames, false);
    size_t count = fileNames.size();

    for (size_t i=0; i<count; i++){
        std::ofstream outfile (fileNames[i] + ".detection_result");
        std::string res = onFrame(cv::imread(fileNames[i]));
        outfile << res << std::endl;
        outfile.close();
    }

}

void Capture::VideoCapture::capture(const std::string& url, const std::function<std::string(cv::Mat)>& onFrame){
    if(url[url.size() - 1] == '/'){
        readDirectory(url, onFrame);
    }else{
        captureVideo(cv::VideoCapture(url), onFrame);
    }
}

void Capture::VideoCapture::capture(const int webcamId, const std::function<std::string(cv::Mat)>& onFrame){
    cv::VideoCapture webcam(webcamId);
    captureVideo(webcam, onFrame);
}