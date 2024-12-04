#include "async_client_node.h"

void async_node_client::ping_call::proceed(bool ok, std::string& server_address, std::string& server_info) {
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

void async_node_client::collect_data_for_distribution_call::proceed(bool ok, std::string& server_address, std::string& server_info) {
    if (ok) {
        if (status.ok()) {
            std::cout << "CollectData from " << collected_data_response.server_address() << " completed successfully: " 
                        << collected_data_response.collected_info() << std::endl;

            server_address += collected_data_response.server_address() + "\n";
            server_info += collected_data_response.collected_info() + "\n";
        } else {
            std::cerr << "CollectData request to " << collect_data_request.to_server_address() << " failed." << std::endl;
        }
    }
}

void async_node_client::async_ping() {
    auto* call = new ping_call(fault_tolerance_stub_, cq_, CALL_TYPE::PING_CALL, to_server_address_);
}

void async_node_client::async_collect_data_for_distribution() {
    auto* call = new collect_data_for_distribution_call(distribution_tasks_stub_, cq_, CALL_TYPE::COLLECT_DATA_FOR_DISTRIBUTION_CALL, to_server_address_);
}

void async_node_client::handle_call(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& server_address, 
                                    std::string& server_info) {
    void* got_tag;
    bool ok = false;

    auto start = std::chrono::high_resolution_clock::now();

    while (cq_.Next(&got_tag, &ok)) {
        // Восстанавливаем объект async_call
        auto* call = static_cast<base_call*>(got_tag);

        // Для защиты от гонки данных строк и счетчика
        std::unique_lock<std::mutex> lock(mtx_);

        call->proceed(ok, server_address, server_info);


        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Processed time: " << duration.count() << std::endl;


        // Уменьшаем счетчик кол-ва запросов
        quant_replies--;
        if (quant_replies == 0) {
            cv.notify_one(); // Уведомляем основной поток о завершении всех запросов
        }

        // Освобождаем память после завершения запроса
        delete call;
    }
}
