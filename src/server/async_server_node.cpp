#include "async_server_node.h"

void async_node_server::Run() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();

    std::cout << "Server listening on " << server_address_ << std::endl;

    // Запускаем обработку RPC запросов
    handle_rpcs();
}

void async_node_server::call_data::proceed(std::vector<std::string> children) {
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

        // TODO: сделаvoid handle_rpcs()ть с помощью condition_variable и mutex
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

void async_node_server::handle_rpcs() {
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

int async_node_server::call_data::getStatusRpc() {
    return status_;
}
