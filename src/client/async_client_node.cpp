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

void async_node_client::process_responses(std::atomic<int>& quant_replies, std::condition_variable& cv, std::string& server_address, 
                                          std::string& server_is_alive) {
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
                    server_is_alive += call->ping_reply.is_alive() + " ";
                } else {
                    std::cerr << "Ping request to " << call->ping_request.to_server_address() << " failed." << std::endl;
                }
            } 
            else if (call->type == async_call::COLLECT_DATA_FOR_DISTRIBUTION) {
                if (call->status.ok()) {
                    std::cout << "CollectData from " << call->collect_data_for_distribution_reply.server_address() << " completed successfully: " 
                              << call->collect_data_for_distribution_reply.collected_info() << std::endl;

                    server_address += call->collect_data_for_distribution_reply.server_address() + " ";
                    server_is_alive += "Data collected: " + call->collect_data_for_distribution_reply.collected_info() + " ";
                } else {
                    std::cerr << "CollectData request to " << call->collect_data_for_distribution_request.to_server_address() << " failed." << std::endl;
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
