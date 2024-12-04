#ifndef ASYNC_CLIENT_NODE_H
#define ASYNC_CLIENT_NODE_H

#include <memory>
#include <thread>
#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <fstream>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using grpc::ClientAsyncReaderWriter;

#include "../../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::FaultToleranceService;
using DistributionSystem::PingRequest;
using DistributionSystem::PingResponse;

using DistributionSystem::DistributionTasksService;
using DistributionSystem::CollectDataRequest;
using DistributionSystem::CollectedData;

enum CALL_TYPE {
    PING_CALL,
    COLLECT_DATA_FOR_DISTRIBUTION_CALL,
    UNKNOWN_CALL
};

enum CALL_STATUS {
    CREATE_CALL, 
    PROCESS_CALL, 
    FINISH_CALL
};

class async_node_client {
public:
    ~async_node_client() {
        cq_.Shutdown();

        // Обработка оставшихся событий после Shutdown
        void* got_tag;
        bool ok;
        while (cq_.Next(&got_tag, &ok)) {
            delete static_cast<base_call*>(got_tag); // Удаление обработанных данных
        }
    }

    explicit async_node_client(std::shared_ptr<Channel> channel, std::string to_server_address)
        : fault_tolerance_stub_(FaultToleranceService::NewStub(channel)),
          distribution_tasks_stub_(DistributionTasksService::NewStub(channel)),
          to_server_address_(to_server_address) {}

    // Асинхронный метод для отправки Ping-запросов
    void async_ping();

    // Асинхронный метод для отправки CollectData-запросов
    void async_collect_data_for_distribution();

    // Обработка результатов асинхронных запросов
    // TODO: сделать обработку переменного числа параметров
    void handle_call(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& server_address, 
                     std::string& server_info);

private:
    class base_call {
    public:
        // TODO: сделать обработку переменного числа параметров
        virtual void proceed(bool ok, std::string& server_address, std::string& server_info) = 0;

        CALL_TYPE call_type_;
        CALL_STATUS call_status_;

        base_call(CALL_TYPE call_type, CALL_STATUS call_status): call_type_(call_type), call_status_(call_status) {}
        virtual ~base_call() = default;
    };

    class ping_call: public base_call {
    public:

        ping_call(std::unique_ptr<FaultToleranceService::Stub>& stub_, CompletionQueue& cq_, CALL_TYPE call_type, 
            std::string to_server_address): base_call(call_type, CREATE_CALL) {
            ping_request.set_to_server_address(to_server_address);
            ping_response_reader = stub_->AsyncPing(&context, ping_request, &cq_);
            ping_response_reader->Finish(&ping_response, &status, (void*)this);
        };

        void proceed(bool ok, std::string& server_address, std::string& server_info) override;

        private:
            std::unique_ptr<ClientAsyncResponseReader<PingResponse>> ping_response_reader;

            ClientContext context;
            Status status;

            PingRequest ping_request;
            PingResponse ping_response;
    };

    class collect_data_for_distribution_call: public base_call {
    public:
        std::unique_ptr<ClientAsyncResponseReader<CollectedData>> collect_data_response_reader;

        ClientContext context;
        Status status;

        CollectDataRequest collect_data_request;
        CollectedData collected_data_response;

        collect_data_for_distribution_call(std::unique_ptr<DistributionTasksService::Stub>& stub_, CompletionQueue& cq_, CALL_TYPE call_type, 
            std::string to_server_address): base_call(call_type, CREATE_CALL) {
                collect_data_request.set_to_server_address(to_server_address);
                collect_data_response_reader = stub_->AsyncCollectData(&context, collect_data_request, &cq_);
                collect_data_response_reader->Finish(&collected_data_response, &status, (void*)this);
            };

        void proceed(bool ok, std::string& server_address, std::string& server_info) override;
    };

    std::unique_ptr<FaultToleranceService::Stub> fault_tolerance_stub_;
    std::unique_ptr<DistributionTasksService::Stub> distribution_tasks_stub_;

    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::string to_server_address_;
    std::mutex mtx_;
};

#endif //!ASYNC_CLIENT_NODE_H
