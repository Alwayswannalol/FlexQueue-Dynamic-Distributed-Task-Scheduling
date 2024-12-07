#ifndef ASYNC_CLIENT_NODE_H
#define ASYNC_CLIENT_NODE_H

#include <memory>
#include <thread>
#include <string>
#include <atomic>
#include <mutex>

#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

#include "../proto/distributionSystem.grpc.pb.h"

using DistributionSystem::FaultToleranceService;
using DistributionSystem::PingRequest;
using DistributionSystem::PingResponse;

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
        : stub_(FaultToleranceService::NewStub(channel)), server_address_(server_address) {}

    // Асинхронный метод для отправки Ping-запросов
    void async_ping() {
        // Используем обычный указатель для управления памятью
        auto* call = new async_call();

        call->request.set_to_server_address(server_address_);

        // Инициализируем асинхронный запрос
        call->response_reader = stub_->PrepareAsyncPing(&call->context, call->request, &cq_);

        // Сохраняем идентификатор запроса и передаем управление на очередь
        call->response_reader->StartCall();
        call->response_reader->Finish(&call->reply, &call->status, reinterpret_cast<void*>(call));
    }

    // Обработка результатов асинхронных запросов
    void process_responses(std::atomic<int>& quant_replies, std::string& server_address, std::string& server_is_alive) {
        void* got_tag;
        bool ok = false;

        while (cq_.Next(&got_tag, &ok)) {
            // Восстанавливаем объект async_call
            auto* call = static_cast<async_call*>(got_tag);

            // Для защиты от гонки данных строк full_string_server_addresses и full_string_server_is_alive и счетчика
            std::unique_lock<std::mutex> lock(mtx_);

            // Проверка очереди 
            if (ok) {
                if (call->status.ok()) {
                    std::cout << "Request to " << call->reply.server_address() << " completed successfully: " 
                            << call->reply.is_alive() << std::endl;

                    server_address += call->reply.server_address() + " ";
                    server_is_alive += call->reply.is_alive() + " ";
                }
                else {
                    std::cerr << "Server " << call->request.to_server_address() << " is dead" << std::endl;

                    server_address += call->request.to_server_address() + " ";
                    server_is_alive += "0 ";
                }
            } 
            else {
                std::cerr << "Error: CompletionQueue returned ok == false" << std::endl;
            }

            // Уменьшаем счетчик кол-ва запросов
            quant_replies--;

            // Освобождаем память после завершения запроса
            delete call;
        }
    }


    // Структура для хранения состояния асинхронного запроса
    struct async_call {
        PingRequest request;
        PingResponse reply;
        ClientContext context;
        Status status;
        std::unique_ptr<ClientAsyncResponseReader<PingResponse>> response_reader;
    };

private:
    std::unique_ptr<FaultToleranceService::Stub> stub_;
    CompletionQueue cq_;  // Общая очередь для всех асинхронных операций
    std::string server_address_;
    std::mutex mtx_;
};

#endif //!ASYNC_CLIENT_NODE_H
