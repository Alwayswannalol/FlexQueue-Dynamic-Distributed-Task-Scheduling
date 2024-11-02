#ifndef ASYNC_CLIENT_NODE_H
#define ASYNC_CLIENT_NODE_H

#include <memory>
#include <thread>
#include <string>
#include <atomic>
#include <mutex>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

#include "../../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::FaultToleranceService;
using DistributionSystem::PingRequest;
using DistributionSystem::PingResponse;

class async_node_client {
public:
    ~async_node_client() {
        cq_.Shutdown();

        // Обработка оставшихся событий после Shutdown
        void* got_tag;
        bool ok;
        while (cq_.Next(&got_tag, &ok)) {
            delete static_cast<async_call*>(got_tag); // Удаление обработанных данных
        }
    }

    explicit async_node_client(std::shared_ptr<Channel> channel, std::string server_address)
        : stub_(FaultToleranceService::NewStub(channel)), server_address_(server_address) {}

    // Асинхронный метод для отправки Ping-запросов
    void async_ping();

    // Обработка результатов асинхронных запросов
    void process_responses(std::atomic<int>& quant_replies, std::string& server_address, std::string& server_is_alive);


    // Структура для хранения состояния асинхронного запроса
    struct async_call {
        PingRequest request;
        PingResponse reply;
        ClientContext context;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<PingResponse>> response_reader;
    };

private:
    std::unique_ptr<FaultToleranceService::Stub> stub_;
    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::string server_address_;
    std::mutex mtx_;
};

#endif //!ASYNC_CLIENT_NODE_H
