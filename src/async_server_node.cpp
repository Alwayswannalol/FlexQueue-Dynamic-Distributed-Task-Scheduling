#include "async_server_node.h"

int main() {
    async_node_server server("0.0.0.0:50051");
    server.Run();
    return 0;
}
