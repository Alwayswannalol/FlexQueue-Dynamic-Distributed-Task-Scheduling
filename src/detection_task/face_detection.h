#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>

class face_detection {
private:
    cv::CascadeClassifier face_cascade;
public:
    face_detection(std::string face_cascade_path) {
        if (!face_cascade.load(face_cascade_path)) {
            std::cerr << "Error loading face cascade!" << std::endl;
        }
    }

    void process_img(std::string path_to_img);
};

#endif //!FACE_DETECTION_H