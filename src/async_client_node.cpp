#include "async_client_node.h"

int main(int argc, char* argv[]) {

    std::string to_server_address;

    if (argc == 2) {
        to_server_address = argv[1];
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    async_node_client client(grpc::CreateChannel(to_server_address, grpc::InsecureChannelCredentials()), to_server_address);

    std::atomic<int> k = 0;
    std::string s1;
    std::string s2;

    std::thread response_thread([&]() {
        client.process_responses(k, s1, s2);
    });

    client.async_ping();

    // Ждем завершения потока обработки ответов
    response_thread.join();

    return 0;
}
