#pragma once

#include <opencv2/opencv.hpp>
#include <yolo_v2_class.hpp>

#include "../darknet/src/image.h"

namespace Support {
    class Time {
    public:
        static long long currentTimeMillis();
    };

    class Detection {
    public:
        int id;
        std::string name;
        Detection(int id, std::string name);
    };

    class OpenCV {
    public:
        static void drawDetections(cv::Mat frame, const std::vector<bbox_t>& detections, std::vector<Detection> &objects);
        static void showWindow(const cv::Mat& frame, int frameDelay);
    };

    class Darknet {
    public:
        static int getObjectsCount(const std::vector<bbox_t> &detections, int objId, float prob = 0.3);
    };

}



struct Label {
    unsigned int id;
    float x{}, y{}, w{}, h{};
    explicit Label(bbox_t detection, float originalWidth, float originalHeight)
            : id(detection.obj_id),
              x(float(detection.x + detection.w / 2.0) / originalWidth),
              y(float((detection.y + detection.h / 2.0) / originalHeight)),
              w(float(detection.w) / originalWidth),
              h(float(detection.h) / originalHeight)
    {}

    [[nodiscard]] std::string toString() const{
        return std::to_string(id) + " " +std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(w) + std::to_string(h);
    }
};
