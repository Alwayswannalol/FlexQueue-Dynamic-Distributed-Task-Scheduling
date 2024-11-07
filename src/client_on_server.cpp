#include "client_on_server/async_client_node.h"

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

        std::condition_variable cv;

        std::thread response_thread([&]() {
            client.process_responses(k, cv, s1, s2);
        });
        
        client.async_collect_data_for_distribution();

        client.async_ping();

        // Ждем завершения потока обработки ответов
        response_thread.join();
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
