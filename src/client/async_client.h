#ifndef ASYNC_CLIENT_H
#define ASYNC_CLIENT_H

#define CHUNK_SIZE 400

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using grpc::ClientAsyncReaderWriter;

#include "../../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::TaskExecutionService;
using DistributionSystem::ImageRequest;
using DistributionSystem::ImageResponse;

#include "../data_collection/files_info.h"

enum CALL_TYPE {
    DETECTION_TASK_EXECUTION_CALL,
    UNKNOWN_CALL
};

class async_client {
public:
    ~async_client() {
        cq_.Shutdown();

        // Обработка оставшихся событий после Shutdown
        void* got_tag;
        bool ok;
        while (cq_.Next(&got_tag, &ok)) {
            delete static_cast<base_call*>(got_tag); // Удаление обработанных данных
        }
    }

    explicit async_client(std::shared_ptr<Channel> channel, std::string to_server_address)
        : task_execution_stub_(TaskExecutionService::NewStub(channel)),
          to_server_address_(to_server_address) {}

    // TODO: передавать в функцию вектор с путями до фотографий
    void async_execute_detection_task();

    // Обработка результатов асинхронных запросов
    // TODO: сделать обработку переменного числа параметров
    void process_responses();

private:
    class base_call {
    public:
        // TODO: сделать обработку переменного числа параметров
        virtual void get_response(bool ok) = 0;

        CALL_TYPE call_type_;
        int get_call_type();

        base_call(CALL_TYPE call_type): call_type_(call_type) {}
        virtual ~base_call() = default;
    };

    class detection_task_execution_call: public base_call {
    public:
        std::unique_ptr<ClientAsyncReaderWriter<ImageRequest, ImageResponse>> responder_;

        ClientContext context;
        Status status;

        ImageRequest image_request;
        ImageResponse image_response;

        detection_task_execution_call(CALL_TYPE call_type): base_call(call_type) {};

        void get_response(bool ok) override;
    };

    std::unique_ptr<TaskExecutionService::Stub> task_execution_stub_;

    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::string to_server_address_;
    std::mutex mtx_;
};

#endif
