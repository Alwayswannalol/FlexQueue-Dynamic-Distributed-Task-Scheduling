#include "client/async_client.h"

int main(int argc, char* argv[]) {
    if (argc == 3) {
        async_client client_distribution(grpc::CreateChannel(argv[1], grpc::InsecureChannelCredentials()), argv[2]);

        std::string response;
        std::atomic<int> requests_count;
        requests_count.store(1);
        std::condition_variable cv;
        std::mutex mtx;

        std::thread distribution_thread([&]() {
            client_distribution.handle_call(requests_count, cv, response);
        });

        std::vector<std::string> filePaths;
        std::string client_name = argv[2];

        if (client_name == "alwayswannalol") {
            filePaths = {"client_photos/client/568430.jpg",
                        "client_photos/client/424590.jpg",
                        "client_photos/client/1087623.jpg"};
        }
        else {
            filePaths = {"client_photos/client/169940.jpg",
                        "client_photos/client/714381.jpg",
                        "client_photos/client/1301061.jpg"};
        }

        task_info task(filePaths.size());

        client_distribution.async_distribute_detection_task(task);

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&requests_count]() { return requests_count.load() == 0; });

        async_client client_execution(grpc::CreateChannel(response, grpc::InsecureChannelCredentials()), argv[2]);

        std::thread execution_thread([&]() {
            client_execution.handle_call(requests_count, cv, response);
        });

        client_execution.async_execute_detection_task(filePaths);

        distribution_thread.join();
        execution_thread.join();
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
