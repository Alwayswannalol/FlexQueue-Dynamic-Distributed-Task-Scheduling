#include "data_collection_server.h"
#include "data_parsing_server.h"


std::string data_collection_server::cmd_execute_read(const char *command){
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return "ERROR";
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return "ERROR";
    } else if (pid == 0) {
        
        close(pipefd[0]);  
        dup2(pipefd[1], STDOUT_FILENO);  
                                        
        dup2(pipefd[1], STDERR_FILENO);  
                                        
        close(pipefd[1]);  

        execlp("sh", "sh", "-c", command, (char *)NULL);

        perror("execlp");
        _exit(EXIT_FAILURE);
    } else {
        
        close(pipefd[1]);  
        std::array<char, 256> buffer;
        std::string result;

        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer.data(), buffer.size())) >0){
            result.append(buffer.data(), bytes_read);
        }
        close(pipefd[0]);  

        int status;
        waitpid(pid, &status, 0);

        // TODO: тут можно добавить логирование
        if (WIFEXITED(status)) {
            
        } else if (WIFSIGNALED(status)) {

        }
    
        return result;
    }
}

std::string data_collection_server::collect_cpu_load(){ //function for the Load CPU for each core
    std::string cpu_load0 = cmd_execute_read("cat /proc/stat");

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::string cpu_load1 = cmd_execute_read("cat /proc/stat");

    std::string cpu_load = data_parsing_server::parse_cpu_load_strings(cpu_load0, cpu_load1);
    return cpu_load;
}

std::string data_collection_server::collect_mem_total(){ //function for total RAM
    std::string mem_total_command = cmd_execute_read("cat /proc/meminfo | grep MemTotal");

    std::string mem_total = data_parsing_server::parse_mem_total_string(mem_total_command);
    return mem_total;
}

std::string data_collection_server::collect_mem_free(){ //function for free RAM
    std::string mem_free_command = cmd_execute_read("cat /proc/meminfo | grep 'MemFree'");

    std::string mem_free = data_parsing_server::parse_mem_free_string(mem_free_command);
    return mem_free;
}

std::string data_collection_server::collect_quant_cores(){ //function for number of cores
    std::string quant_cores_command = cmd_execute_read("cat /proc/cpuinfo | grep 'cpu cores'");

    std::string quant_cores = data_parsing_server::parse_quant_cores_string(quant_cores_command);
    return quant_cores;
}

std::string data_collection_server::collect_cpu_freq(){ //function for average frequency across cores
    std::string cpu_freq_command = cmd_execute_read("cat /proc/cpuinfo | grep 'cpu MHz'");

    std::string cpu_freq = data_parsing_server::parse_cpu_freq_string(cpu_freq_command);
    return cpu_freq;
}
