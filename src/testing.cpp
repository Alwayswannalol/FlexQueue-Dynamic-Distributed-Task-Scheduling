#include "async_client_node.h"
#include "async_server_node.h"

int main() {
    async_node_server master_node("0.0.0.0:50051", {"0.0.0.0:50052"});
    std::thread mater_node_run([&]() {
        try {
            master_node.Run();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in master_node.Run(): " << e.what() << std::endl;
        }
        });
    std::this_thread::sleep_for(std::chrono::seconds(1));

    async_node_server node1("0.0.0.0:50052", {"0.0.0.0:50053"});
    std::thread node1_run([&]() {
        try {
            node1.Run();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in node1.Run(): " << e.what() << std::endl;
        }
    });
    std::this_thread::sleep_for(std::chrono::seconds(1));

    async_node_server node2("0.0.0.0:50053", {});
    std::thread node2_run([&]() {
        try {
            node2.Run();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in node2.Run(): " << e.what() << std::endl;
        }
    });
    std::this_thread::sleep_for(std::chrono::seconds(1));

    async_node_client* client = new async_node_client(grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials()), "0.0.0.0:50051");

    std::atomic<int> quant_requests = 1;
    std::string s1;
    std::string s2;

    std::thread response_thread([&]() {
        try {
            client->process_responses(quant_requests, s1, s2);
        } catch (const std::exception& e) {
            std::cerr << "Exception in response_thread: " << e.what() << std::endl;
        }
    });
    
    client->async_ping();

    // Ждем завершения потока обработки ответов
    response_thread.detach();

    while (quant_requests > 0) {
        continue;
    }

    // Удаление клиента и серверов
    delete client;

    mater_node_run.join();
    node1_run.join();
    node2_run.join();

    return 0;
}
