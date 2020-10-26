#include "modules/capture/VideoCapture.h"
#include "yolo_v2_class.hpp"
#include "modules/util/Util.h"
#define GPU 0
#define MESSAGE "WARNING"


int main(int argc, char* argv[]) {
    std::string url;
    int webcamId = -1;
    int waitKeyDelay = 1;
    bool isImage = true;
    if(argc > 1){
        try {
            webcamId = std::stoi(argv[1]);
            isImage = false;
        } catch (std::exception &e){
            url = argv[1];
        }
        if(argc > 2)
            waitKeyDelay = std::stoi(argv[2]);
    }
    Util::Detection person(0, "person");
    Util::Detection phone(67, "phone");
    Util::Detection book(73, "book");
    Util::Detection remote(65, "calculator");
    std::vector<Util::Detection> objects = {
            person,
            phone,
            book,
            remote
    };
    Detector detector(
            "resources/yolov4.cfg",
            "resources/yolov4.weights",
            0
    );

    auto detect = [&](cv::Mat frame) {
        const std::vector<bbox_t> &detections = detector.detect(frame, 0.525, true);
        const int personsCount = Util::Darknet::getObjectsCount(detections, 0.5, person.id);
        Util::OpenCV::drawDetections(frame, detections, objects);
        if (personsCount > 1) {
            cv::putText(frame, MESSAGE, cvPoint(0, 90), cv::FONT_HERSHEY_COMPLEX_SMALL, 5, cvScalar(0, 0, 255), 5,
                        CV_GRAY2RGBA);
        }
        cv::imshow("DETECTION", frame);
        cv::waitKey(waitKeyDelay);
    };

    cv::namedWindow("DETECTION");
    if(!isImage){
        Capture::VideoCapture::capture(webcamId, detect);
    }else{
        Capture::VideoCapture::capture(url, detect);
    }

    return 0;
}
