cmake_minimum_required(VERSION 3.11)

project(Async)

find_package(Protobuf CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(server src/async_server_node.cpp proto/distributionSystemService.grpc.pb.cc proto/distributionSystemService.pb.cc)
add_executable(client src/async_client_node.cpp proto/distributionSystemService.grpc.pb.cc proto/distributionSystemService.pb.cc)

target_link_libraries(server PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
target_link_libraries(client PRIVATE gRPC::grpc++ gRPC::grpc gRPC::grpc++_reflection protobuf::libprotobuf)
