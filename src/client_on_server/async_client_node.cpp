#include "async_client_node.h"

int async_node_client::base_call::get_call_type() {
    return call_type_;
}

void async_node_client::ping_call::get_response(bool ok, std::string& server_address, std::string& server_info) {
    if (ok) {
        if (status.ok()) {
            std::cout << "Ping to " << ping_response.server_address() << " completed successfully: " 
                      << ping_response.is_alive() << std::endl;

            server_address += ping_response.server_address() + " ";
            server_info += ping_response.is_alive() + " ";
        }
    }
    else {
        std::cerr << "Error: CompletionQueue returned ok == false" << std::endl;
    }
}

void async_node_client::collect_data_for_distribution_call::get_response(bool ok, std::string& server_address, std::string& server_info) {
    if (ok) {
        if (status.ok()) {
            std::cout << "CollectData from " << collected_data_response.server_address() << " completed successfully: " 
                        << collected_data_response.collected_info() << std::endl;

            server_address += collected_data_response.server_address() + " ";
            server_info += "Data collected: " + collected_data_response.collected_info() + " ";
        } else {
            std::cerr << "CollectData request to " << collect_data_request.to_server_address() << " failed." << std::endl;
        }
    }
}

void async_node_client::async_ping() {
    // Используем обычный указатель для управления памятью
    auto* call = new ping_call(CALL_TYPE::PING_CALL);

    call->ping_request.set_to_server_address(to_server_address_);

    // Инициализируем асинхронный запрос
    call->ping_response_reader = fault_tolerance_stub_->PrepareAsyncPing(&call->context, call->ping_request, &cq_);

    // Сохраняем идентификатор запроса и передаем управление на очередь
    call->ping_response_reader->StartCall();
    call->ping_response_reader->Finish(&call->ping_response, &call->status, reinterpret_cast<void*>(call));
}

void async_node_client::async_collect_data_for_distribution() {
    auto* call = new collect_data_for_distribution_call(CALL_TYPE::COLLECT_DATA_FOR_DISTRIBUTION_CALL);

    call->collect_data_request.set_to_server_address(to_server_address_);

    call->collect_data_response_reader = distribution_tasks_stub_->PrepareAsyncCollectData(&call->context, call->collect_data_request, &cq_);
    call->collect_data_response_reader->StartCall();
    call->collect_data_response_reader->Finish(&call->collected_data_response, &call->status, reinterpret_cast<void*>(call));
}

void async_node_client::process_responses(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& server_address, 
                                          std::string& server_info) {
    void* got_tag;
    bool ok = false;

    while (cq_.Next(&got_tag, &ok)) {
        // Восстанавливаем объект async_call
        auto* call = static_cast<base_call*>(got_tag);

        // Для защиты от гонки данных строк и счетчика
        std::unique_lock<std::mutex> lock(mtx_);

        call->get_response(ok, server_address, server_info);

        // Уменьшаем счетчик кол-ва запросов
        quant_replies--;
        if (quant_replies == 0) {
            cv.notify_one(); // Уведомляем основной поток о завершении всех запросов
        }

        // Освобождаем память после завершения запроса
        delete call;
    }
}
