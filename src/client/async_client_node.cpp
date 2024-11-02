#include "async_client_node.h"

void async_node_client::async_ping() {
    // Используем обычный указатель для управления памятью
    auto* call = new async_call();

    call->request.set_to_server_address(server_address_);

    // Инициализируем асинхронный запрос
    call->response_reader = stub_->PrepareAsyncPing(&call->context, call->request, &cq_);

    // Сохраняем идентификатор запроса и передаем управление на очередь
    call->response_reader->StartCall();
    call->response_reader->Finish(&call->reply, &call->status, reinterpret_cast<void*>(call));
}

void async_node_client::process_responses(std::atomic<int>& quant_replies, std::string& server_address, std::string& server_is_alive) {
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
