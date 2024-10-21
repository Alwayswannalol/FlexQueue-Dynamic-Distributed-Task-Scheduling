#ifndef ASYNC_SERVER_NODE_H
#define ASYNC_SERVER_NODE_H

#include <memory>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>

using grpc::CompletionQueue;
using grpc::Server;

#include "../proto/distributionSystemService.grpc.pb.h"

class async_node_server {
public:
    ~async_node_server() {
        server_->Shutdown();
        cq_->Shutdown();
    }

    explicit async_node_server(const std::string& server_address)
        : server_address_(server_address) {}

    void Run() {
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
        builder.RegisterService(&service_);
        cq_ = builder.AddCompletionQueue();
        server_ = builder.BuildAndStart();

        std::cout << "Server listening on " << server_address_ << std::endl;

        // Запускаем обработку RPC запросов
        handle_rpcs();
    }

private:
    class call_data {
    public:
        call_data(distributionSystemService::DistributionSystemService::AsyncService* service,
                 grpc::ServerCompletionQueue* cq)
            : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
            proceed();
        }

        void proceed() {
            if (status_ == CREATE) {
                status_ = PROCESS;
                // Запрашиваем новое событие Ping
                service_->RequestPing(&ctx_, &request_, &responder_, cq_, cq_, this);
            } else if (status_ == PROCESS) {
                new call_data(service_, cq_);  // Для обработки нового запроса создаем новый объект call_data

                // Формируем ответ на запрос Ping
                response_.set_server_address(request_.num());
                response_.set_is_alive(true);
                status_ = FINISH;
                responder_.Finish(response_, grpc::Status::OK, this);
            } else {
                delete this;
            }
        }

    private:
        distributionSystemService::DistributionSystemService::AsyncService* service_;
        grpc::ServerCompletionQueue* cq_;
        grpc::ServerContext ctx_;

        distributionSystemService::Empty request_;
        distributionSystemService::PingResponse response_;
        grpc::ServerAsyncResponseWriter<distributionSystemService::PingResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;  // Текущий статус RPC
    };

    void handle_rpcs() {
        new call_data(&service_, cq_.get());

        void* tag;
        bool ok;
        while (true) {
            cq_->Next(&tag, &ok);
            if (ok) {
                static_cast<call_data*>(tag)->proceed();
            }
        }
    }

    std::string server_address_;
    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    distributionSystemService::DistributionSystemService::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
};

#endif //ASYNC_SERVER_NODE_H
