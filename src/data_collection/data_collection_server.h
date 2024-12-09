#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>

class data_collection_server {
private:
    static std::string cmd_execute_read(const char *command);
public:
    static std::string collect_cpu_load();
    static std::string collect_mem_total();
    static std::string collect_mem_free();
    static std::string collect_quant_cores();
    static std::string collect_cpu_freq();
};
