#ifndef ASYNC_CLIENT_H
#define ASYNC_CLIENT_H

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 4000000
#endif

#include <condition_variable>
#include <thread>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using grpc::ClientAsyncReaderWriter;

#include "../../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::TaskExecutionService;
using DistributionSystem::TaskInfoRequest;
using DistributionSystem::PathResponse;

using DistributionSystem::ImageRequest;
using DistributionSystem::ImageResponse;

#include "../data_collection/files_info.h"

enum CALL_TYPE {
    DISTRIBUTE_DETECTION_TASK_CALL,
    DETECTION_TASK_EXECUTION_CALL,
    UNKNOWN_CALL
};

enum CALL_STATUS {
    CREATE_CALL, 
    PROCESS_CALL, 
    FINISH_CALL
};

struct task_info {
    int num_photo;
    task_info (int num_photo_): num_photo(num_photo_) {}
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

    explicit async_client(std::shared_ptr<Channel> channel, std::string client_name)
        : task_execution_stub_(TaskExecutionService::NewStub(channel)), client_name_(client_name) {
            result_dir_ = "tmp/" + client_name + "_result/";
            std::filesystem::create_directories(result_dir_);
        }

    void async_distribute_detection_task(task_info task);

    void async_execute_detection_task(std::vector<std::string> filePaths);

    // Обработка rpc_calls
    // TODO: сделать обработку переменного числа параметров
    void handle_call(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& response);

private:
    class base_call {
    public:
        CALL_TYPE call_type_;
        CALL_STATUS call_status_;


        base_call(CALL_TYPE call_type, CALL_STATUS call_status): call_type_(call_type), call_status_(call_status) {}
        virtual ~base_call() = default;

        // TODO: сделать обработку переменного числа параметров
        virtual void proceed(bool ok, std::string& response) = 0;
    };

    class distribute_detection_task_call: public base_call {
    public:
        distribute_detection_task_call(std::unique_ptr<TaskExecutionService::Stub>& stub_, CompletionQueue& cq_, CALL_TYPE call_type, task_info task, std::string client_name)
            : base_call(call_type, CREATE_CALL), client_name_(client_name) {
                task_request.set_task_data("num_photo: " + std::to_string(task.num_photo));
                path_response_reader = stub_->AsyncDistributeDetectionTask(&context, task_request, &cq_);
                path_response_reader->Finish(&path_response, &status, (void*)this);
            }

        void proceed(bool ok, std::string& response) override;
    private:
        std::unique_ptr<ClientAsyncResponseReader<PathResponse>> path_response_reader;

        ClientContext context;
        Status status;

        TaskInfoRequest task_request;
        PathResponse path_response;
        
        std::string client_name_;
    };

    class detection_task_execution_call: public base_call {
    public:
        detection_task_execution_call(std::unique_ptr<TaskExecutionService::Stub>& stub_, CompletionQueue& cq_, CALL_TYPE call_type, 
                                      std::vector<std::string> filePaths, std::string client_name, std::string result_dir)
            : base_call(call_type, CREATE_CALL), writing_mode_(true),
              filePaths_(filePaths), counter_(0), client_name_(client_name), result_dir_(result_dir) {
            responder_ = stub_->AsyncExecuteDetectionTask(&context, &cq_, (void*)this);
            call_status_ = PROCESS_CALL;
        };

        void proceed(bool ok, std::string& response) override;
    private:

        std::unique_ptr<ClientAsyncReaderWriter<ImageRequest, ImageResponse>> responder_;

        ClientContext context;
        Status status;

        ImageRequest request_;
        ImageResponse response_;

        bool writing_mode_;

        std::vector<std::string> filePaths_;
        int counter_;

        std::ifstream reading_stream;
        std::string prev_filepath_;
        int size;
        int num_of_chunk;

        std::ofstream writing_stream;
        std::string prev_filename_;

        std::string client_name_;
        std::string result_dir_;
    };

    std::unique_ptr<TaskExecutionService::Stub> task_execution_stub_;

    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::mutex mtx_;

    std::string client_name_;
    std::string result_dir_;
};

#endif
