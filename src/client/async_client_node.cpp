#include "async_client_node.h"

void async_node_client::async_ping() {
    // Используем обычный указатель для управления памятью
    auto* call = new async_call();
    call->type = async_call::PING;

    call->ping_request.set_to_server_address(server_address_);

    // Инициализируем асинхронный запрос
    call->ping_response_reader = fault_tolerance_stub_->PrepareAsyncPing(&call->context, call->ping_request, &cq_);

    // Сохраняем идентификатор запроса и передаем управление на очередь
    call->ping_response_reader->StartCall();
    call->ping_response_reader->Finish(&call->ping_reply, &call->status, reinterpret_cast<void*>(call));
}

void async_node_client::async_collect_data_for_distribution() {
    auto* call = new async_call();
    call->type = async_call::COLLECT_DATA_FOR_DISTRIBUTION;

    call->collect_data_for_distribution_request.set_to_server_address(server_address_);

    call->collect_data_for_distribution_response_reader = distribution_tasks_stub_->PrepareAsyncCollectData(&call->context, call->collect_data_for_distribution_request, &cq_);
    call->collect_data_for_distribution_response_reader->StartCall();
    call->collect_data_for_distribution_response_reader->Finish(&call->collect_data_for_distribution_reply, &call->status, reinterpret_cast<void*>(call));
}

// TODO: передавать вектор с путями до изображений
void async_node_client::async_execute_detection_task() {
    auto* call = new async_call();
    call->type = async_call::EXECUTE_DETECTION_TASK;

    call->photo_stream = execution_task_stub_->AsyncExecuteDetectionTask(&call->context, &cq_, this);

    call->photo_data_request.set_client_name("Egor");

    call->photo_stream->Write(call->photo_data_request, this);

    // char data_for_server[CHUNK_SIZE];
    // std::string filepath = "/home/egor/work/code/FlexQueue/FlexQueue-Dynamic-Distributed-Task-Scheduling/tmp/client/1.jpg";

    // std::ifstream read_photo(filepath);

    // int size_photo = files_info::get_size(filepath);

    // if (!read_photo.is_open()) {
    //     std::cerr << "Error in opening file" << std::endl;
    // }

    // int numOfChunk = 1;

    // while(numOfChunk * CHUNK_SIZE <= size_photo) {
        // TODO: добавить имя клиента в конструктор класса
        // read_photo.read(data_for_server, CHUNK_SIZE);

        // std::cout << data_for_server << std::endl;

        // call->photo_data_request.set_client_name("client1");
        // call->photo_data_request.set_filename("1.jpg");
        // call->photo_data_request.set_path_to_destination_node("0.0.0.0:50051");
        // call->photo_data_request.set_is_last_chunk_of_photo(false);
        // call->photo_data_request.set_is_last_photo(true);
        // call->photo_data_request.set_data(data_for_server, read_photo.gcount());

        // std::cout << "there" << std::endl;

        // std::this_thread::sleep_for(std::chrono::seconds(10));

        // call->photo_stream->Write(call->photo_data_request, this);

    // }
    // if (numOfChunk * CHUNK_SIZE != size_photo) {
        // read_photo.read(data_for_server, CHUNK_SIZE);

        // call->photo_data_request.set_client_name("client1");
        // call->photo_data_request.set_filename("1.jpg");
        // call->photo_data_request.set_path_to_destination_node("0.0.0.0:50051");
        // call->photo_data_request.set_is_last_chunk_of_photo(true);
        // call->photo_data_request.set_is_last_photo(true);
        // std::cout << "HERE1 " << sizeof(data_for_server) << read_photo.gcount() << std::endl;
        // call->photo_data_request.set_data(data_for_server, read_photo.gcount());
        // std::cout << "HERE2" << std::endl;

        // call->photo_stream->Write(call->photo_data_request, this);
    // }

    // read_photo.close();

    // call->photo_stream->Read(&call->photo_data_response, this);
    // delete call;
}

void async_node_client::process_responses(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& server_address, 
                                          std::string& server_info) {
    void* got_tag;
    bool ok = false;

    while (cq_.Next(&got_tag, &ok)) {
        // Восстанавливаем объект async_call
        auto* call = static_cast<async_call*>(got_tag);

        // Для защиты от гонки данных строк и счетчика
        std::unique_lock<std::mutex> lock(mtx_);

        // Проверка очереди 
        if (ok) {
            if (call->type == async_call::PING) {
                if (call->status.ok()) {
                    std::cout << "Ping to " << call->ping_reply.server_address() << " completed successfully: " 
                              << call->ping_reply.is_alive() << std::endl;

                    server_address += call->ping_reply.server_address() + " ";
                    server_info += call->ping_reply.is_alive() + " ";
                } else {
                    std::cerr << "Ping request to " << call->ping_request.to_server_address() << " failed." << std::endl;
                }
            } 
            else if (call->type == async_call::COLLECT_DATA_FOR_DISTRIBUTION) {
                if (call->status.ok()) {
                    std::cout << "CollectData from " << call->collect_data_for_distribution_reply.server_address() << " completed successfully: " 
                              << call->collect_data_for_distribution_reply.collected_info() << std::endl;

                    server_address += call->collect_data_for_distribution_reply.server_address() + " ";
                    server_info += "Data collected: " + call->collect_data_for_distribution_reply.collected_info() + " ";
                } else {
                    std::cerr << "CollectData request to " << call->collect_data_for_distribution_request.to_server_address() << " failed." << std::endl;
                }
            }
            else if (call->type == async_call::EXECUTE_DETECTION_TASK) {
                // Обработка ответов от сервера в bidi RPC
                if (call->status.ok()) {
                    // Печатаем или сохраняем полученные данные
                    std::cout << "Size of photo data: " << call->photo_data_response.data().length() << std::endl;

                    // Запрашиваем следующий ответ
                    call->photo_stream->Read(&call->photo_data_response, this);
                } else {
                    // Завершение потока, если сервер прекратил отправку
                    std::cerr << "Detection task response stream ended." << std::endl;
                }
            }
        } 
        else {
            std::cerr << "Error: CompletionQueue returned ok == false" << std::endl;
        }

        // Уменьшаем счетчик кол-ва запросов
        quant_replies--;
        if (quant_replies == 0) {
            cv.notify_one(); // Уведомляем основной поток о завершении всех запросов
        }

        // Освобождаем память после завершения запроса
        delete call;
    }
}
