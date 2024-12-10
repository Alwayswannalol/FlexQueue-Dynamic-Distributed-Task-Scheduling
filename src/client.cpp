#include "client/async_client.h"

#include <thread>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        async_client client(grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials()), "alwayswannalol");

        std::thread response_thread([&]() {
            client.handle_call();
        });

        std::vector<std::string> filePaths = {"tmp/client/1.jpg",
                                              "tmp/client/2.jpg",
                                              "tmp/client/3.jpg"};
        // std::vector<std::string> filePaths = {"tmp/client/3.jpg"};

        client.async_execute_detection_task(filePaths);

        // Ждем завершения потока обработки ответов
        response_thread.join();
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
