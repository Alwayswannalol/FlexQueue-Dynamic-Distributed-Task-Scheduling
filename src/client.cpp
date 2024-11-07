#include "client/async_client.h"

#include <thread>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        async_client client(grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials()));

        std::thread response_thread([&]() {
            client.handle_call();
        });

        client.async_execute_detection_task();

        // Ждем завершения потока обработки ответов
        response_thread.join();
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
