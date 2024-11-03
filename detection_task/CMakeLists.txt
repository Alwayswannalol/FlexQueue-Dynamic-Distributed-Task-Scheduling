cmake_minimum_required(VERSION 3.10)
project(FaceTask)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(face_detection face_detection.cpp)
target_link_libraries(face_detection ${OpenCV_LIBS})

