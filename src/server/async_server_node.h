#ifndef ASYNC_SERVER_NODE_H
#define ASYNC_SERVER_NODE_H

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 4000000
#endif

#include <memory>
#include <vector>
#include <string>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <cstdio>

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
using DistributionSystem::TaskInfoRequest;
using DistributionSystem::PathResponse;

using DistributionSystem::ImageRequest;
using DistributionSystem::ImageResponse;

using DistributionSystem::ScalabilityService;
using DistributionSystem::TopologyRequest;
using DistributionSystem::TopologyResponse;

#include "../client_on_server/async_client_node.h"
#include "../data_collection/data_collection_server.h"
#include "../data_collection/files_info.h"
#include "../detection_task/face_detection.h"
#include "../scheduling_algorithm/WLC.h"

enum RPC_TYPE {
    PING,
    COLLECT_DATA_FOR_DISTRIBUTION,
    DISTRIBUTE_DETECTION_TASK,
    DETECTION_TASK_EXECUTION,
    GET_TOPOLOGY,
    UNKNOWN
};

enum RPC_STATUS {
    CREATE_RPC, 
    PROCESS_RPC, 
    FINISH_RPC
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
                delete static_cast<base_rpc*>(got_tag);
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
        virtual void proceed(bool ok, std::vector<std::string> children, std::string server_dir) = 0;

        base_rpc(RPC_TYPE rpc_type, RPC_STATUS status): rpc_type_(rpc_type), status_(status) {}
        virtual ~base_rpc() = default;
        
        RPC_STATUS status_;
        RPC_TYPE rpc_type_;
    };

    // Класс для обработки Ping RPC
    class ping_rpc: public base_rpc {
    public:
        ping_rpc(FaultToleranceService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, 
        std::vector<std::string> children, std::string server_dir)
            : base_rpc(rpc_type, CREATE_RPC), service_(service), cq_(cq), responder_(&ctx_) {
            proceed(true, children, server_dir);
        }

        void proceed(bool ok, std::vector<std::string> children, std::string server_dir) override;

    private:
        FaultToleranceService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        PingRequest request_;
        PingResponse response_;
        ServerAsyncResponseWriter<PingResponse> responder_;
    };

    // Класс для обработки CollectData RPC
    class collect_data_for_distribution_rpc: public base_rpc {
    public:
        collect_data_for_distribution_rpc(DistributionTasksService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, 
        std::vector<std::string> children, std::string server_dir)
            : base_rpc(rpc_type, CREATE_RPC), service_(service), cq_(cq), responder_(&ctx_) {
            proceed(true, children, server_dir);
        }

        void proceed(bool ok, std::vector<std::string> children, std::string server_dir) override;

    private:
        DistributionTasksService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        CollectDataRequest request_;
        CollectedData response_;
        ServerAsyncResponseWriter<CollectedData> responder_;
    };

    // Класс для обработки GetTopology RPC
    class get_topology_rpc: public base_rpc {
    public:
        get_topology_rpc(ScalabilityService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type,
        std::vector<std::string> children, std::string server_dir)
            : base_rpc(rpc_type, CREATE_RPC), service_(service), cq_(cq), responder_(&ctx_) {
                proceed(true, children, server_dir);
            }
        
        void proceed(bool ok, std::vector<std::string> children, std::string server_dir) override;

        private:
            ScalabilityService::AsyncService* service_;
            ServerCompletionQueue* cq_;
            ServerContext ctx_;

            TopologyRequest request_;
            TopologyResponse response_;
            ServerAsyncResponseWriter<TopologyResponse> responder_;
    };

    class distribute_detection_task_rpc: public base_rpc {
    public:
        distribute_detection_task_rpc(TaskExecutionService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, 
        std::vector<std::string> children, std::string server_dir)
            : base_rpc(rpc_type, CREATE_RPC), service_(service), cq_(cq), responder_(&ctx_) {
            proceed(true, children, server_dir);
        }

        void proceed(bool ok, std::vector<std::string> children, std::string server_dir) override;

    private:
        TaskExecutionService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        TaskInfoRequest request_;
        PathResponse response_;
        ServerAsyncResponseWriter<PathResponse> responder_;
    };

    // Класс для обработки DetectionTaskExecution RPC
    class detection_task_execution_rpc: public base_rpc {
    public:
        detection_task_execution_rpc(TaskExecutionService::AsyncService* service, ServerCompletionQueue* cq, RPC_TYPE rpc_type, 
        std::vector<std::string> children, std::string server_dir)
            : base_rpc(rpc_type, CREATE_RPC), service_(service), cq_(cq), responder_(&ctx_), 
              writing_mode_(false), new_responder_created_(false), counter_(0), last_packet_(false),
              detection_task(server_dir + "/src/detection_task/haarcascade_frontalface_alt.xml") {
            proceed(true, children, server_dir);
        }
        
        void proceed(bool ok, std::vector<std::string> children, std::string server_dir) override;

    private:
        TaskExecutionService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        ImageRequest request_;
        ImageResponse response_;
        ServerAsyncReaderWriter<ImageResponse, ImageRequest> responder_;

        bool writing_mode_;
        bool new_responder_created_;

        bool last_packet_;

        std::ofstream writing_stream_;
        std::string prev_filename_;
        std::vector<std::string> filenames_;

        int counter_;
        std::ifstream reading_stream_;
        int num_of_chunk_;
        int size_;

        face_detection detection_task;

        std::mutex mtx_;
    };

    void handle_rpcs();

    std::string server_address_;
    std::vector<std::string> children_;
    std::string server_dir_;

    std::unique_ptr<ServerCompletionQueue> cq_;
    FaultToleranceService::AsyncService fault_tolerance_service_;
    DistributionTasksService::AsyncService distribution_tasks_service_;
    ScalabilityService::AsyncService scalability_service_;
    TaskExecutionService::AsyncService task_execution_service_;
    
    std::unique_ptr<Server> server_;
};

#endif //!ASYNC_SERVER_NODE_H
