#include "modules/capture/VideoCapture.h"
#include "yolo_v2_class.hpp"
#include "modules/util/Util.h"
#define GPU 0
#define MESSAGE "WARNING"

bool need2ShowWarning(const std::function<int(std::vector<bbox_t>)>& condition){

}

int main(int argc, char* argv[]) {
    int webcamId = 0;
    if(argc > 1){
        webcamId = std::stoi(argv[1]);
    }
    Util::Detection person(0, "person");
    Util::Detection phone(67, "phone");
    std::vector<Util::Detection> objects = {person, phone};
    Detector detector(
            "resources/yolov4.cfg",
            "resources/yolov4.weights",
            0
    );
    cv::namedWindow("DETECTION");
    Capture::VideoCapture::capture("video.mp4", [&](cv::Mat frame) {

        const std::vector<bbox_t> &detections = detector.detect(frame, 0.525, true);
        const int personsCount = Util::Darknet::getObjectsCount(detections, 0.5, person.id);
        Util::OpenCV::drawDetections(frame, detections, objects);
        if(personsCount > 1){
            cv::putText(frame, MESSAGE, cvPoint(0, 90),cv::FONT_HERSHEY_COMPLEX_SMALL, 5, cvScalar(0,0,255), 5, CV_GRAY2RGBA);
        }
        cv::imshow("DETECTION", frame);
        cv::waitKey(1);
    });
    return 0;
}
