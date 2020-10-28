#include "Util.h"


#include <chrono>
#include <utility>


long long Util::Util::currentTimeMillis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

void Util::OpenCV::drawDetections(cv::Mat frame, const std::vector<bbox_t> &detections, std::vector<Detection> &objects) {
    for (auto &object: objects) {
        for (auto &i : detections) {
            if (i.obj_id == object.id && i.prob > 0.7) {
                cv::Scalar color = obj_id_to_color(i.obj_id);
                cv::rectangle(frame, cv::Rect(i.x, i.y, i.w, i.h), color, 2);
                std::string obj_name = object.name;
                if (i.track_id > 0) obj_name += " - " + std::to_string(i.track_id);
                cv::Size const text_size = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2, 0);
                int max_width = (text_size.width > i.w + 2) ? text_size.width : (i.w + 2);
                max_width = std::max(max_width, (int) i.w + 2);
                std::string coords_3d;
                if (!std::isnan(i.z_3d)) {
                    std::stringstream ss;
                    ss << std::fixed << std::setprecision(2) << "x:" << i.x_3d << "m y:" << i.y_3d << "m z:"
                       << i.z_3d << "m ";
                    coords_3d = ss.str();
                    cv::Size const text_size_3d = getTextSize(ss.str(), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, 1, 0);
                    int const max_width_3d = (text_size_3d.width > i.w + 2) ? text_size_3d.width : (i.w + 2);
                    if (max_width_3d > max_width) max_width = max_width_3d;
                }
                cv::rectangle(frame, cv::Point2f(std::max((int) i.x - 1, 0), std::max((int) i.y - 35, 0)),
                              cv::Point2f(std::min((int) i.x + max_width, frame.cols - 1),
                                          std::min((int) i.y, frame.rows - 1)),
                              color, CV_FILLED, 8, 0);
                putText(frame, obj_name, cv::Point2f(i.x, i.y - 16), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2,
                        cv::Scalar(0, 0, 0), 2);
                if (!coords_3d.empty())
                    putText(frame, coords_3d, cv::Point2f(i.x, i.y - 1), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8,
                            cv::Scalar(0, 0, 0), 1);
            }
        }
    }
}

int Util::Darknet::getObjectsCount(const std::vector<bbox_t> &detections, int objId, float prob) {
    int count = 0;
    for (auto detection : detections) {
        if (detection.prob >= prob && detection.obj_id == objId) {
            count++;
        }
    }
    return count;
}

Util::Detection::Detection(int id, std::string name) : id(id), name(std::move(name)) {}
void Util::OpenCV::showWindow(const cv::Mat &frame, int frameDelay) {
    cv::imshow("DETECTION", frame);
    cv::waitKey(frameDelay);
}