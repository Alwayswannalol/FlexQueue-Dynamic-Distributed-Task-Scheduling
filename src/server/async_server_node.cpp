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

void async_node_server::execute_detection_rpc::proceed(std::vector<std::string> children) {
    const char* data_from_client;

    if (status_ == CREATE) {
        status_ = START_PROCESS;
        service_->RequestExecuteDetectionTask(&ctx_, &responder_, cq_, cq_, this);
    } 
    else if (status_ == START_PROCESS) {
        new execute_detection_rpc(service_, cq_, RPC_TYPE::EXECUTE_DETECTION_TASK, children);
        status_ = READ;
        responder_.Read(&request_, this);
    }
    else if (status_ == READ) {
        // TODO: когда будет обработка функции proceed с переменным числом параметров, можно будет передавать server_dir_, пока захардкодил
        if (!write_photo) {
            if (!std::filesystem::exists("/home/egor/work/code/FlexQueue/FlexQueue-Dynamic-Distributed-Task-Scheduling/tmp/" + request_.client_name())) {
                std::filesystem::create_directories("/home/egor/work/code/FlexQueue/FlexQueue-Dynamic-Distributed-Task-Scheduling/tmp/" + request_.client_name());
            }

            // TODO: убрать output_, когда будет внедрена обработка
            write_photo.open("/home/egor/work/code/FlexQueue/FlexQueue-Dynamic-Distributed-Task-Scheduling/tmp/" + request_.client_name() + "/output_" + std::to_string(num_photo) + ".jpg", std::ios::app);
        }

        data_from_client = request_.data().c_str();

        if (!write_photo) {
            std::cerr << "Error in writing file" << std::endl;
        }

        write_photo.write(data_from_client, request_.data().length());

        if (request_.is_last_chunk_of_photo()) {
            write_photo.close();
            num_photo++;
        }

        if (request_.is_last_chunk_of_photo() && request_.is_last_photo()) {
            // TODO: выполнение задачи
            status_ = WRITE;
        }
        else {
            responder_.Read(&request_, this);
        }
    }
    else if (status_ == WRITE) {
        char data_for_client[CHUNK_SIZE];
        // TODO: отправка клиенту ответа
        for (int i = 1; i <= num_photo; i++) {
            std::string filepath = "/home/egor/work/code/FlexQueue/FlexQueue-Dynamic-Distributed-Task-Scheduling/tmp/" + request_.client_name() + "/output_" + std::to_string(i) + ".jpg";

            std::ifstream read_photo(filepath);
            int size_photo = files_info::get_size(filepath);

            int numOfChunk = 1;

            read_photo.read(data_for_client, CHUNK_SIZE);
            while(numOfChunk * CHUNK_SIZE <= size_photo) {
                response_.set_filename("output" + std::to_string(i) + ".jpg");
                response_.set_is_last_chunk_of_photo(false);
                if (i == num_photo) {
                    response_.set_is_last_photo(true);
                }
                response_.set_data(data_for_client, read_photo.gcount());
                responder_.Write(response_, this);
            }
            if (numOfChunk * CHUNK_SIZE != size_photo) {
                response_.set_filename("output" + std::to_string(i) + ".jpg");
                response_.set_is_last_chunk_of_photo(true);
                if (i == num_photo) {
                    response_.set_is_last_photo(true);
                }
                response_.set_data(data_for_client, read_photo.gcount());
                responder_.Write(response_, this);
            }

            read_photo.close();

            responder_.Finish(grpc::Status::OK, this);
        }
        status_ = FINISH;
    }
    else {
        delete this;
    }
}

void async_node_server::handle_rpcs() {
    new collect_data_for_distribution_rpc(&distribution_tasks_service_, cq_.get(), RPC_TYPE::COLLECT_DATA_FOR_DISTRIBUTION, children_);
    new ping_rpc(&fault_tolerance_service_, cq_.get(), RPC_TYPE::PING, children_);
    new execute_detection_rpc(&task_execution_service_, cq_.get(), RPC_TYPE::EXECUTE_DETECTION_TASK, children_);

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
