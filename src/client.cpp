#include "client/async_client_node.h"

int main(int argc, char* argv[]) {
    std::vector<std::string> children;

    std::string to_server_address;

    if (argc == 2) {
        to_server_address = argv[1];

        async_node_client client(grpc::CreateChannel(to_server_address, grpc::InsecureChannelCredentials()), to_server_address);

        std::atomic<int> k;
        k.store(0);
        std::string s1;
        std::string s2;

        std::thread response_thread([&]() {
            client.process_responses(k, s1, s2);
        });
        
        client.async_ping();

        // Ждем завершения потока обработки ответов
        response_thread.join();
    }
    else if (argc > 2) {
        for (int i = 1; i < argc; i++) {
            children.push_back(argv[i]);
        }

        std::string full_string_server_addresses = "";
        std::string full_string_server_is_alive = "";

        // Сколько запросов надо сделать
        std::atomic<int> requests_count;
        requests_count.store(children.size());

        // Создаем клиентов для опроса дочерних узлов
        std::vector<async_node_client*> child_clients;
        for (const std::string& child: children) {
            child_clients.push_back(new async_node_client(grpc::CreateChannel(child, grpc::InsecureChannelCredentials()), child));
        }

        for (auto& child_client: child_clients) {
            std::thread([child_client, &requests_count, &full_string_server_addresses, &full_string_server_is_alive]() {
                child_client->process_responses(requests_count, full_string_server_addresses, full_string_server_is_alive); // Запуск метода обработки ответов
            }).detach();
            child_client->async_ping();
        }

        while (requests_count > 0) {
            continue;
        }

        // Удаление клиентов
        for (async_node_client* child_client: child_clients) {
            delete child_client;
        }
        child_clients.clear();
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
