#ifndef ASYNC_SERVER_NODE_H
#define ASYNC_SERVER_NODE_H

#include <memory>
#include <vector>
#include <string>
#include <atomic>

#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::ServerAsyncResponseWriter;

#include "../../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::FaultToleranceService;
using DistributionSystem::PingRequest;
using DistributionSystem::PingResponse;

#include "../client/async_client_node.h"

class async_node_server {
public:
    ~async_node_server() {
        server_->Shutdown();
        cq_->Shutdown();

        // Обработка оставшихся событий после Shutdown
        void* got_tag;
        bool ok;
        while (cq_->Next(&got_tag, &ok)) {
            if (ok) {
                delete static_cast<call_data*>(got_tag); // Удаление обработанных данных
            }
        }
    }

    explicit async_node_server(const std::string& server_address, std::vector<std::string> children)
        : server_address_(server_address), children_(std::move(children)) {}

    void Run();

private:
    class call_data {
    public:
        call_data(FaultToleranceService::AsyncService* service,
                 ServerCompletionQueue* cq, std::vector<std::string> children)
            : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
            proceed(children);
        }

        void proceed(std::vector<std::string> children);

        int getStatusRpc();

    private:
        FaultToleranceService::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;

        PingRequest request_;
        PingResponse response_;
        ServerAsyncResponseWriter<PingResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // Текущий статус RPC
    };

    void handle_rpcs();

    std::string server_address_;
    std::vector<std::string> children_;

    std::unique_ptr<ServerCompletionQueue> cq_;
    FaultToleranceService::AsyncService service_;
    std::unique_ptr<Server> server_;
};

#endif //!ASYNC_SERVER_NODE_H
