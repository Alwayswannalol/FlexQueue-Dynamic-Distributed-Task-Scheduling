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

#include "../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::FaultToleranceService;
using DistributionSystem::PingRequest;
using DistributionSystem::PingResponse;

#include "async_client_node.h"

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
        call_data(FaultToleranceService::AsyncService* service,
                 ServerCompletionQueue* cq, std::vector<std::string> children)
            : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
            proceed(children);
        }

        void proceed(std::vector<std::string> children) {
            if (status_ == CREATE) {
                status_ = PROCESS;
                // Запрашиваем новое событие Ping
                service_->RequestPing(&ctx_, &request_, &responder_, cq_, cq_, this);
            } 
            else if (status_ == PROCESS) {
                new call_data(service_, cq_, children);  // Для обработки нового запроса создаем новый объект call_data

                std::string full_string_server_addresses = "";
                std::string full_string_server_is_alive = "";

                // Сколько запросов надо сделать
                std::atomic<int> requests_count;
                requests_count.store(children.size());

                // Создаем клиентов для опроса дочерних узлов
                std::vector<std::shared_ptr<async_node_client>> child_clients;
                for (const std::string& child : children) {
                    child_clients.push_back(std::make_shared<async_node_client>(
                        grpc::CreateChannel(child, grpc::InsecureChannelCredentials()), child));
                }

                for (auto& child_client: child_clients) {
                    std::thread([this, child_client, &requests_count, &full_string_server_addresses, &full_string_server_is_alive]() {
                        child_client->process_responses(requests_count, full_string_server_addresses, full_string_server_is_alive); // Запуск метода обработки ответов
                    }).detach();
                    child_client->async_ping();
                }

                // TODO: сделать с помощью condition_variable и mutex
                while (requests_count > 0) {
                    continue;
                }

                // Формируем ответ на запрос Ping с учетом дочерних узлов
                response_.set_server_address(full_string_server_addresses + request_.to_server_address());
                response_.set_is_alive(full_string_server_is_alive + "1");
                status_ = FINISH;
                responder_.Finish(response_, grpc::Status::OK, this);
            } 
            else {
                if (status_ == FINISH) {
                    delete this;
                }
            }
        }

        int getStatusRpc() {
            return status_;
        }

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

    void handle_rpcs() {
        new call_data(&service_, cq_.get(), children_);

        void* tag;
        bool ok;
        while (true) {
            cq_->Next(&tag, &ok);
            if (ok) {
                std::cout << "Processing tag: " << tag << std::endl;
                // static_cast<call_data*>(tag)->proceed(children_);
                std::cout << "StatusRpc: " << static_cast<call_data*>(tag)->getStatusRpc() << std::endl;
                static_cast<call_data*>(tag)->proceed(children_);
            } 
            else {
                std::cerr << "Error: ServerCompletionQueue returned false" << std::endl;
            }
        }
    }

    std::string server_address_;
    std::vector<std::string> children_;

    std::unique_ptr<ServerCompletionQueue> cq_;
    FaultToleranceService::AsyncService service_;
    std::unique_ptr<Server> server_;
};

#endif //!ASYNC_SERVER_NODE_H
