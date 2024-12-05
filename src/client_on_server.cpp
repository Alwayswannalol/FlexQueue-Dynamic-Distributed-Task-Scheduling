#include "client_on_server/async_client_node.h"
// #define TEST_100

int main(int argc, char* argv[]) {
    std::vector<std::string> children;

    std::string to_server_address;

    if (argc == 2) {
        to_server_address = argv[1];

        #ifndef TEST_100
        async_node_client client(grpc::CreateChannel(to_server_address, grpc::InsecureChannelCredentials()), to_server_address);

        std::atomic<int> k;
        k.store(0);
        std::string s1;
        std::string s2;

        std::condition_variable cv;

        std::thread response_thread([&]() {
            client.handle_call(k, cv, s1, s2);
        });
        
        client.async_get_topology();

        // Ждем завершения потока обработки ответов
        response_thread.join();
        #endif

        #ifdef TEST_100
        std::vector<std::shared_ptr<async_node_client>> clients;
        for (int i = 0; i < 100; i++) {
            clients.push_back(std::make_shared<async_node_client>(grpc::CreateChannel(to_server_address, grpc::InsecureChannelCredentials()), 
                                to_server_address));
        }

        std::atomic<int> requests_count;
        requests_count.store(clients.size());
        std::condition_variable cv;
        std::mutex mtx;
        std::string s1;
        std::string s2;

        for (auto& client: clients) {
            std::thread([client, &requests_count, &cv, &s1, &s2]() {
                client->handle_call(requests_count, cv, s1, s2); // Запуск метода обработки ответов
            }).detach();
            client->async_collect_data_for_distribution();
        }

        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&requests_count]() { return requests_count.load() == 0; });
        #endif
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    return 0;
}
