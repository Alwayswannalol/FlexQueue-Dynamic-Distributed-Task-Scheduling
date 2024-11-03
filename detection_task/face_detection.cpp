#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    // Проверьте, что указано достаточное количество аргументов
    if (argc < 2) {
        std::cout << "Usage: ./face_detection <image_path1> <image_path2> ... <image_path10>" << std::endl;
        return -1;
    }

    // Загружаем каскадный классификатор для распознавания лиц
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("/home/miha/FaceTask/haarcascade_frontalface_alt.xml")) {
        std::cout << "Error loading face cascade!" << std::endl;
        return -1;
    }

    // Обработка изображений
    for (int i = 1; i < argc && i < 11; ++i) { // Обрабатываем до 10 изображений
        std::string imagePath = argv[i];
        cv::Mat image = cv::imread(imagePath);
        if (image.empty()) {
            std::cout << "Could not read the image: " << imagePath << std::endl;
            continue;
        }

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(image, faces);

        // Рисуем рамки вокруг обнаруженных лиц
        for (const auto& face : faces) {
            cv::rectangle(image, face, cv::Scalar(255, 0, 0), 2);
        }

        // Сохраняем результат
        std::string outputFilename = "output_" + std::to_string(i) + ".jpg";
        cv::imwrite(outputFilename, image);
        std::cout << "Detection completed for: " << imagePath << ". Results saved to " << outputFilename << std::endl;
    }

    return 0;
}
