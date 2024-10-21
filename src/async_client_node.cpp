#include "async_client_node.h"

int main() {
    async_node_client client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::thread response_thread([&]() {
        client.process_responses();
    });

    // Отправляем несколько асинхронных запросов
    for (int i = 0; i < 5; ++i) {
        std::cout << "Sending request " << i << std::endl;
        client.async_ping(i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Ждем завершения потока обработки ответов
    response_thread.join();

    return 0;
}
