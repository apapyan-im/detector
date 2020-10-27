#include "modules/capture/VideoCapture.h"
#include "yolo_v2_class.hpp"
#include "modules/util/Util.h"

#define MESSAGE "WARNING"


int main(int argc, char* argv[]) {
    std::string url;
    int webcamId = -1;
    int waitKeyDelay = 1;
    bool isWebcam = false;
    if(argc > 1){
        try {
            webcamId = std::stoi(argv[1]);
            isWebcam = true;
        } catch (std::exception &e){
            url = argv[1];
        }
        if(argc > 2)
            waitKeyDelay = std::stoi(argv[2]);
    }
    std::vector<Util::Detection> objects = {
            {0, "person"},
            {67, "phone"},
            {73, "book"}
    };
    Detector detector(
            "resources/yolov4.cfg",
            "resources/yolov4.weights",
            0
    );

    auto detect = [&](cv::Mat frame) {
        const std::vector<bbox_t> &detections = detector.detect(frame, 0.3);
        const int personsCount = Util::Darknet::getObjectsCount(detections, objects[0].id);
        const int phonesCount = Util::Darknet::getObjectsCount(detections, objects[1].id);
        Util::OpenCV::drawDetections(frame, detections, objects);
        if (personsCount > 1 || phonesCount > 0) {
            cv::putText(
                frame,
                MESSAGE,
                cvPoint(0, 90),
                cv::FONT_HERSHEY_COMPLEX_SMALL,
                5,
                cvScalar(0, 0, 255),
                5,
                CV_GRAY2RGBA
            );
        }
        cv::imshow("DETECTION", frame);
        cv::waitKey(waitKeyDelay);
    };

    cv::namedWindow("DETECTION");
    if(isWebcam){
        Capture::VideoCapture::capture(webcamId, detect);
    }else{
        Capture::VideoCapture::capture(url, detect);
    }

    return 0;
}
