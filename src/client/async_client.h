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

enum CALL_STATUS {
    CREATE_CALL, 
    PROCESS_CALL, 
    FINISH_CALL
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

    explicit async_client(std::shared_ptr<Channel> channel)
        : task_execution_stub_(TaskExecutionService::NewStub(channel)) {}

    // TODO: передавать в функцию вектор с путями до фотографий
    void async_execute_detection_task();

    // Обработка rpc_calls
    // TODO: сделать обработку переменного числа параметров
    void handle_call();

private:
    class base_call {
    public:
        CALL_TYPE call_type_;
        CALL_STATUS call_status_;


        base_call(CALL_TYPE call_type, CALL_STATUS call_status): call_type_(call_type), call_status_(call_status) {}
        virtual ~base_call() = default;

        // TODO: сделать обработку переменного числа параметров
        virtual void proceed(bool ok) = 0;
    };

    class detection_task_execution_call: public base_call {
    public:

        detection_task_execution_call(std::unique_ptr<TaskExecutionService::Stub>& stub_, CompletionQueue& cq_, CALL_TYPE call_type)
            : base_call(call_type, CREATE_CALL), writing_mode_(true), 
            counter(0), test_str({"1 from client", "2 from client"}) {
            responder_ = stub_->AsyncExecuteDetectionTask(&context, &cq_, (void*)this);
            call_status_ = PROCESS_CALL;
        };

        void proceed(bool ok) override;
    private:

        std::unique_ptr<ClientAsyncReaderWriter<ImageRequest, ImageResponse>> responder_;

        ClientContext context;
        Status status;

        ImageRequest request_;
        ImageResponse response_;

        bool writing_mode_;

        // TODO: для тестирования
        int counter;
        std::vector<std::string> test_str;
    };

    std::unique_ptr<TaskExecutionService::Stub> task_execution_stub_;

    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::mutex mtx_;
};

#endif
