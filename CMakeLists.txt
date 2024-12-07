cmake_minimum_required(VERSION 3.11)

project(Async)

# Сборка с отладочной информацией
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

find_package(Protobuf CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(server src/async_server_node.cpp proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)
add_executable(client src/async_client_node.cpp proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

target_link_libraries(server PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
target_link_libraries(client PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)

#for testing all system
add_executable(test src/testing.cpp proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)
target_link_libraries(test PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
