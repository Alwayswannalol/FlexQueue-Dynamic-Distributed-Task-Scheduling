#ifndef ASYNC_SERVER_NODE_H
#define ASYNC_SERVER_NODE_H

#define CHUNK_SIZE 400

#include <memory>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <filesystem>
#include <fstream>

#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerAsyncReaderWriter;

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

#include "../client_on_server/async_client_node.h"
#include "../data_collection/files_info.h"

enum RPC_TYPE {
    PING,
    COLLECT_DATA_FOR_DISTRIBUTION,
    DETECTION_TASK_EXECUTION,
    UNKNOWN
};

class async_node_server {
public:
    ~async_node_server() {
        server_->Shutdown();
        cq_->Shutdown();

        void* got_tag;
        bool ok;
        while (cq_->Next(&got_tag, &ok)) {
            if (ok) {
                delete static_cast<ping_rpc*>(got_tag);
                delete static_cast<collect_data_for_distribution_rpc*>(got_tag);
            }
        }
    }

    explicit async_node_server(const std::string& server_address, std::string server_dir, std::vector<std::string> children)
        : server_address_(server_address), children_(std::move(children)), server_dir_(server_dir) {}

    void Run();

private:
    class base_rpc {
    public:
        // TODO: сделать обработку переменного числа параметров
        virtual void proceed(std::vector<std::string> children) = 0;

        RPC_TYPE rpc_type_;
        int get_rpc_type();

        base_rpc(RPC_TYPE rpc_type): rpc_type_(rpc_type) {}
        virtual ~base_rpc() = default;
    };

    // Класс для обработки Ping RPC
    class ping_rpc: public base_rpc {
    public:
        ping_rpc(FaultToleranceService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, std::vector<std::string> children)
            : base_rpc(rpc_type), service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
            proceed(children);
        }

        void proceed(std::vector<std::string> children) override;

        int get_status_rpc();

    private:
        FaultToleranceService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        PingRequest request_;
        PingResponse response_;
        ServerAsyncResponseWriter<PingResponse> responder_;
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;
    };

    // Класс для обработки CollectData RPC
    class collect_data_for_distribution_rpc: public base_rpc {
    public:
        collect_data_for_distribution_rpc(DistributionTasksService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, std::vector<std::string> children)
            : base_rpc(rpc_type), service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
            proceed(children);
        }

        void proceed(std::vector<std::string> children) override;

        int get_status_rpc();

    private:
        DistributionTasksService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        CollectDataRequest request_;
        CollectedData response_;
        ServerAsyncResponseWriter<CollectedData> responder_;
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;
    };

    class detection_task_execution_rpc: public base_rpc {
    public:
        detection_task_execution_rpc(TaskExecutionService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, std::vector<std::string> children)
            : base_rpc(rpc_type), service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {}
        
        void proceed(std::vector<std::string> children) override;

        int get_status_rpc();

    private:
        TaskExecutionService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        ImageRequest request_;
        ImageResponse response_;
        ServerAsyncReaderWriter<ImageRequest, ImageResponse> responder_;
        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;
    };

    void handle_rpcs();

    std::string server_address_;
    std::vector<std::string> children_;
    std::string server_dir_;

    std::unique_ptr<ServerCompletionQueue> cq_;
    FaultToleranceService::AsyncService fault_tolerance_service_;
    DistributionTasksService::AsyncService distribution_tasks_service_;
    TaskExecutionService::AsyncService task_execution_service_;
    
    std::unique_ptr<Server> server_;
};

#endif //!ASYNC_SERVER_NODE_H
