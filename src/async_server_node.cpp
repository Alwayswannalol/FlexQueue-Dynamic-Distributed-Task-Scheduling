#include "async_server_node.h"

int main(int argc, char* argv[]) {

    std::string server_address;
    std::vector<std::string> children;

    if (argc == 2) {
        server_address = argv[1];
    }
    else if (argc > 2) {
        server_address = argv[1];
        for (int i = 2; i < argc; i++) {
            children.push_back(argv[i]);
        }
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    async_node_server server(server_address, children);
    server.Run();
    return 0;
}
