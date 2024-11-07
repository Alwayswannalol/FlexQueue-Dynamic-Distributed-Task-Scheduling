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

add_executable(server src/server.cpp src/server/async_server_node.cpp 
src/client_on_server/async_client_node.cpp
proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

add_executable(client_on_server src/client_on_server.cpp src/client_on_server/async_client_node.cpp
proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

add_executable(client src/client.cpp src/client/async_client.cpp
proto/distributionSystem.grpc.pb.cc proto/distributionSystem.pb.cc)

target_link_libraries(server PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
target_link_libraries(client_on_server PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
target_link_libraries(client PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
