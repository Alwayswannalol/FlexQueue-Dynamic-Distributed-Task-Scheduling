#include "server/async_server_node.h"

int main(int argc, char* argv[]) {
    std::string server_address;
    std::string server_dir;
    std::vector<std::string> children;

    if (argc == 3) {
        server_dir = argv[1];
        server_address = argv[2];
    }
    else if (argc > 3) {
        server_dir = argv[1];
        server_address = argv[2];
        for (int i = 3; i < argc; i++) {
            children.push_back(argv[i]);
        }
    }
    else {
        std::cerr << "Error" << std::endl;
    }

    async_node_server server(server_address, server_dir, children);
    server.Run();
    
    return 0;
}
