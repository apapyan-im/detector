#pragma once

#include <opencv2/opencv.hpp>
#include <yolo_v2_class.hpp>

#include "../darknet/src/image.h"

namespace Util {
    class Util {
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
    };

    class Darknet {
    public:
        static int getObjectsCount(const std::vector<bbox_t> &detections, int objId, float prob = 0.7);
    };

}

