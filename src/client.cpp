#include "client/async_client.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        async_client client(grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials()), "alwayswannalol");

        std::filesystem::create_directories("tmp/results");

        std::string response;
        std::atomic<int> requests_count;
        requests_count.store(1);
        std::condition_variable cv;
        std::mutex mtx;

        std::thread response_thread([&]() {
            client.handle_call(requests_count, cv, response);
        });

        std::vector<std::string> filePaths = {"client_photos/client/1.jpg",
                                              "client_photos/client/2.jpg",
                                              "client_photos/client/3.jpg"};
                                              
        task_info task(filePaths.size());

        client.async_distribute_detection_task(task);

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&requests_count]() { return requests_count.load() == 0; });

        client.async_execute_detection_task(filePaths);

        // Ждем завершения потока обработки ответов
        response_thread.join();
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
