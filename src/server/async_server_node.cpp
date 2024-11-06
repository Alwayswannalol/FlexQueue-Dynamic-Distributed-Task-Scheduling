#include "async_server_node.h"

void async_node_server::Run() {
    if (!std::filesystem::exists(server_dir_ + "/tmp")) {
        std::filesystem::create_directories(server_dir_ + "/tmp");
    }

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());

    builder.RegisterService(&fault_tolerance_service_);
    builder.RegisterService(&distribution_tasks_service_);
    builder.RegisterService(&task_execution_service_);

    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();

    std::cout << "Server listening on " << server_address_ << std::endl;

    // Запускаем обработку RPC запросов
    handle_rpcs();
}

int async_node_server::base_rpc::get_rpc_type() {
    return rpc_type_;
}

void async_node_server::ping_rpc::proceed(std::vector<std::string> children) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        // Запрашиваем новое событие Ping
        service_->RequestPing(&ctx_, &request_, &responder_, cq_, cq_, this);
    } 
    else if (status_ == PROCESS) {
        new ping_rpc(service_, cq_, RPC_TYPE::PING, children);  // Для обработки нового запроса создаем новый объект ping_rpc

        std::string full_string_server_addresses = "";
        std::string full_string_server_is_alive = "";

        // Сколько запросов надо сделать
        std::atomic<int> requests_count;
        requests_count.store(children.size());

        std::mutex mtx;
        std::condition_variable cv;

        // Создаем клиентов для опроса дочерних узлов
        std::vector<std::shared_ptr<async_node_client>> child_clients;
        for (const std::string& child : children) {
            child_clients.push_back(std::make_shared<async_node_client>(
                grpc::CreateChannel(child, grpc::InsecureChannelCredentials()), child));
        }

        for (auto& child_client: child_clients) {
            std::thread([this, child_client, &requests_count, &cv, &full_string_server_addresses, &full_string_server_is_alive]() {
                child_client->process_responses(requests_count, cv, full_string_server_addresses, full_string_server_is_alive); // Запуск метода обработки ответов
            }).detach();
            child_client->async_ping();
        }

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&requests_count]() { return requests_count.load() == 0; });

        // Формируем ответ на запрос Ping с учетом дочерних узлов
        response_.set_server_address(full_string_server_addresses + request_.to_server_address());
        response_.set_is_alive(full_string_server_is_alive + "1");
        status_ = FINISH;
        responder_.Finish(response_, grpc::Status::OK, this);
    } 
    else {
        delete this;
    }
}

int async_node_server::ping_rpc::get_status_rpc() {
    return status_;
}

void async_node_server::collect_data_for_distribution_rpc::proceed(std::vector<std::string> children) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestCollectData(&ctx_, &request_, &responder_, cq_, cq_, this);
    } 
    else if (status_ == PROCESS) {
        new collect_data_for_distribution_rpc(service_, cq_, RPC_TYPE::COLLECT_DATA_FOR_DISTRIBUTION, children);  // Для обработки нового запроса создаем новый объект collect_data_for_distribution_rpc

        std::string full_string_server_addresses = "";
        std::string full_string_collected_data_for_distribution = "";

        // Сколько запросов надо сделать
        std::atomic<int> requests_count;
        requests_count.store(children.size());

        std::mutex mtx;
        std::condition_variable cv;

        // Создаем клиентов для опроса дочерних узлов
        std::vector<std::shared_ptr<async_node_client>> child_clients;
        for (const std::string& child : children) {
            child_clients.push_back(std::make_shared<async_node_client>(
                grpc::CreateChannel(child, grpc::InsecureChannelCredentials()), child));
        }

        for (auto& child_client: child_clients) {
            std::thread([this, child_client, &requests_count, &cv, &full_string_server_addresses, &full_string_collected_data_for_distribution]() {
                child_client->process_responses(requests_count, cv, full_string_server_addresses, full_string_collected_data_for_distribution); // Запуск метода обработки ответов
            }).detach();
            child_client->async_collect_data_for_distribution();
        }

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&requests_count]() { return requests_count.load() == 0; });

        // TODO: написать сбор данных
        response_.set_server_address(full_string_server_addresses + request_.to_server_address());
        response_.set_collected_info(full_string_collected_data_for_distribution + "2");
        //

        status_ = FINISH;
        responder_.Finish(response_, grpc::Status::OK, this);
    } 
    else {
        delete this;
    }
}

int async_node_server::collect_data_for_distribution_rpc::get_status_rpc() {
    return status_;
}

void async_node_server::handle_rpcs() {
    new collect_data_for_distribution_rpc(&distribution_tasks_service_, cq_.get(), RPC_TYPE::COLLECT_DATA_FOR_DISTRIBUTION, children_);
    new ping_rpc(&fault_tolerance_service_, cq_.get(), RPC_TYPE::PING, children_);

    void* tag;
    bool ok;
    while (true) {
        cq_->Next(&tag, &ok);
        if (ok) {
            auto rpc_call = static_cast<base_rpc*>(tag);

            std::cout << "Processing tag: " << tag << std::endl; 
            std::cout << "Processing rpc_type: " << rpc_call->rpc_type_ << std::endl; 

            rpc_call->proceed(children_);
        } 
        else {
            std::cerr << "Error: ServerCompletionQueue returned false" << std::endl;
        }
    }
}
