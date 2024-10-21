#ifndef ASYNC_CLIENT_NODE_H
#define ASYNC_CLIENT_NODE_H

#include <memory>
#include <thread>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

#include "../proto/distributionSystemService.grpc.pb.h"

using distributionSystemService::DistributionSystemService;
using distributionSystemService::Empty;
using distributionSystemService::PingResponse;

class async_node_client {
public:
    explicit async_node_client(std::shared_ptr<Channel> channel)
        : stub_(DistributionSystemService::NewStub(channel)) {}

    // Асинхронный метод для отправки Ping-запросов
    void async_ping(int request_id) {
        // Используем обычный указатель для управления памятью
        auto* call = new async_call();

        call->request.set_num(std::to_string(request_id));

        // Инициализируем асинхронный запрос
        call->response_reader = stub_->PrepareAsyncPing(&call->context, call->request, &cq_);

        // Сохраняем идентификатор запроса и передаем управление на очередь
        call->response_reader->StartCall();
        call->response_reader->Finish(&call->reply, &call->status, reinterpret_cast<void*>(call));
    }

    // Обработка результатов асинхронных запросов
    void process_responses() {
        void* got_tag;
        bool ok = false;

        while (cq_.Next(&got_tag, &ok)) {
            // Восстанавливаем объект AsyncCall
            auto* call = static_cast<async_call*>(got_tag);

            if (ok) {
                std::cout << "Request to " << call->reply.server_address() << " completed successfully: " 
                          << call->reply.is_alive() << std::endl;
            } else {
                std::cerr << "Request failed!" << std::endl;
            }

            // Освобождаем память после завершения запроса
            delete call;
        }
    }


    // Структура для хранения состояния асинхронного запроса
    struct async_call {
        Empty request;
        PingResponse reply;
        ClientContext context;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<PingResponse>> response_reader;
    };

private:
    std::unique_ptr<DistributionSystemService::Stub> stub_;
    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
};

#endif //ASYNC_CLIENT_NODE_H
