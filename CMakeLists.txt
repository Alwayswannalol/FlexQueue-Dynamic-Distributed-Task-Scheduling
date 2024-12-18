cmake_minimum_required(VERSION 3.11)

project(Async)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Сборка с отладочной информацией
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

find_package(Protobuf CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(server src/server.cpp src/server/async_server_node.cpp 
src/client_on_server/async_client_node.cpp
src/data_collection/data_collection_server.cpp
src/data_collection/data_parsing_server.cpp
src/data_collection/files_info.cpp
src/detection_task/face_detection.cpp
proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

add_executable(client_on_server src/client_on_server.cpp src/client_on_server/async_client_node.cpp
src/data_collection/files_info.cpp
proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

add_executable(client src/client.cpp src/client/async_client.cpp
src/data_collection/files_info.cpp
proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

target_link_libraries(server ${OpenCV_LIBS} gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
target_link_libraries(client_on_server gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
target_link_libraries(client gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
