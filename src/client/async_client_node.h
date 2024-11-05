#ifndef ASYNC_CLIENT_NODE_H
#define ASYNC_CLIENT_NODE_H

#define CHUNK_SIZE 400

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

using DistributionSystem::TaskExecutionService;
using DistributionSystem::ImageRequest;
using DistributionSystem::ImageResponse;

#include "../data_collection/files_info.h"

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
        : fault_tolerance_stub_(FaultToleranceService::NewStub(channel)),
          distribution_tasks_stub_(DistributionTasksService::NewStub(channel)),
          execution_task_stub_(TaskExecutionService::NewStub(channel)),
          server_address_(server_address) {}

    // Асинхронный метод для отправки Ping-запросов
    void async_ping();

    // Асинхронный метод для отправки CollectData-запросов
    void async_collect_data_for_distribution();

    void async_execute_detection_task();

    // Обработка результатов асинхронных запросов
    // TODO: можно сделать обработку переменного числа параметров в зависимости от rpc вызова
    void process_responses(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& server_address, 
                           std::string& server_is_alive);

private:
    // Структура для хранения состояния асинхронного запроса
    // TODO: можно разделить так же как base_rpc
    struct async_call {
        enum CallType { PING, COLLECT_DATA_FOR_DISTRIBUTION, EXECUTE_DETECTION_TASK } type;

        PingRequest ping_request;
        PingResponse ping_reply;

        CollectDataRequest collect_data_for_distribution_request;
        CollectedData collect_data_for_distribution_reply;

        ImageRequest photo_data_request;
        ImageResponse photo_data_response;

        ClientContext context;
        Status status;

        std::unique_ptr<ClientAsyncResponseReader<PingResponse>> ping_response_reader;
        std::unique_ptr<ClientAsyncResponseReader<CollectedData>> collect_data_for_distribution_response_reader;
        std::unique_ptr<ClientAsyncReaderWriter<ImageRequest, ImageResponse>> photo_stream;
    };

    std::unique_ptr<FaultToleranceService::Stub> fault_tolerance_stub_;
    std::unique_ptr<DistributionTasksService::Stub> distribution_tasks_stub_;
    std::unique_ptr<TaskExecutionService::Stub> execution_task_stub_;

    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::string server_address_;
    std::mutex mtx_;
};

#endif //!ASYNC_CLIENT_NODE_H
