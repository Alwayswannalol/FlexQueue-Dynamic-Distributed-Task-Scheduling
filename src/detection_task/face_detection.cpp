#include "face_detection.h"
#include "../data_collection/files_info.h"

void face_detection::process_img(std::string path_to_img) {
    std::string filename = files_info::get_filename(path_to_img);
    std::string filepath = files_info::get_path(path_to_img);

    cv::Mat image = cv::imread(path_to_img);

    if (image.empty()) {
        std::cout << "Could not read the image: " << path_to_img << std::endl;
        return;
    }

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(image, faces);

    for (const auto& face : faces) {
        cv::rectangle(image, face, cv::Scalar(255, 0, 0), 2);
    }

    std::string outputFilename = filepath + "/output_" + filename;
    cv::imwrite(outputFilename, image);
}
