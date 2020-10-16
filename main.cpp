#include "modules/capture/VideoCapture.h"
#include "yolo_v2_class.hpp"
#include "modules/util/Util.h"

#define MESSAGE "WARNING"



int main(int argc, char* argv[]) {
    std::string src;
    int webcamId = 0;

    if(argc > 1){
        webcamId = std::stoi(argv[1]);
    }
//    const std::string MESSAGE = "WARNING";

    Util::Detection person(0, "person");
    std::vector<Util::Detection> objects = {person};
    Detector detector(
            "/home/art/Workspace/detector/modules/darknet/cfg/yolov4.cfg",
            "/home/art/Workspace/detector/resources/yolov4.weights",
            0
    );
    cv::namedWindow("DETECTION");
    Capture::VideoCapture::capture("rtsp://127.0.0.1:1337/test", [&](cv::Mat frame) {
        const std::vector<bbox_t> &detections = detector.detect(frame, 0.25, true);
        int personsCount = Util::Darknet::getObjectsCount(detections, 0.6, person.id);
        Util::OpenCV::drawDetections(frame, detections, objects);
        if(personsCount > 1){
            cv::putText(frame, MESSAGE, cvPoint(0, 90),cv::FONT_HERSHEY_COMPLEX_SMALL, 5, cvScalar(0,0,255), 5, CV_GRAY2RGBA);
        }
        cv::imshow("DETECTION", frame);
        cv::waitKey(1);
    });
    return 0;
}
