#include "dataCollection.h"
#include "parsingServer.h"


std::string DataCollectionServer::CmdExecuteRead(const char *command){
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
        if (WIFEXITED(status)) {
//            ALOG_DataCollection("Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
//            ALOG_DataCollection("Child killed by signal %d\n", WTERMSIG(status));
        }
    
        return result;
    }
}

std::string DataCollectionServer::CPULoadDataCollection(){ //function for the Load CPU for each core
    std::vector<std::string> load_cpu;
        
    std::string cmd = "cat /proc/stat" ;
    std::string result = CmdExecuteRead(cmd.c_str());
    load_cpu.push_back(result);
    sleep(1);

    result = CmdExecuteRead(cmd.c_str());
    load_cpu.push_back(result);

    std::string CPU_load = ServerInfo::parseCpuLoadFile(load_cpu[0], load_cpu[1]);
    return CPU_load;
}

std::string DataCollectionServer::MemTotalDataCollection(){ //function for total RAM 
    std::string cmd = "cat /proc/meminfo | grep MemTotal" ;
    std::string total_memory = CmdExecuteRead(cmd.c_str());

    std::string Total_ = ServerInfo::parseMemTotalFile(total_memory);
    return Total_;
}

std::string DataCollectionServer::MemFreeDataCollection(){ //function for free RAM
    std::string cmd = "cat /proc/meminfo | grep 'MemFree'" ;
    std::string free_memory = CmdExecuteRead(cmd.c_str());

    std::string Free_ = ServerInfo::parseMemFreeFile(free_memory);
    return Free_;
}

std::string DataCollectionServer::CoresDataCollection(){ //function for number of cores
    std::string cmd = "cat /proc/cpuinfo | grep 'cpu cores'" ;
    std::string number_cores = CmdExecuteRead(cmd.c_str());

    std::string Cores_ = ServerInfo::parseCoresFile(number_cores);
    return Cores_;
}

std::string DataCollectionServer::FreqDataCollection(){ //function for average frequency across cores
    std::string cmd = "cat /proc/cpuinfo | grep 'cpu MHz'" ;
    std::string cpuHz = CmdExecuteRead(cmd.c_str());

    std::string Freq_ = ServerInfo::parseFreqAvg(cpuHz);
    return Freq_;
}
