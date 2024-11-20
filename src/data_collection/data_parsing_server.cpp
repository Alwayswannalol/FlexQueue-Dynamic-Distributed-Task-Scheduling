#include "data_parsing_server.h"

std::string data_parsing_server::get_cpu_load_data(std::vector<double> cpu_load_clusters) {
    std::stringstream ss;
    for (size_t i = 0; i < cpu_load_clusters.size(); ++i) {
        if (i != 0) ss << " ";
        ss << cpu_load_clusters[i];
    }
    return ss.str();
}

std::string data_parsing_server::parse_mem_total_string(const std::string mem_total_command) {
    unsigned long long mem_total_Kb;
    std::string label;

    std::istringstream str(mem_total_command);
    str >> label >> mem_total_Kb;

    std::string add_ = "MemTotalKb: ";
    std::string mem_total = std::to_string(mem_total_Kb);
    mem_total.insert(0, add_);
    return mem_total;
}

std::string data_parsing_server::parse_mem_free_string(const std::string mem_free_command) {
    unsigned long long mem_free_Kb;
    std::string label;

    std::istringstream str(mem_free_command);
    str >> label >> mem_free_Kb;

    std::string add_ = "MemFreeKb: ";
    std::string mem_free = std::to_string(mem_free_Kb);
    mem_free.insert(0, add_);
    return mem_free;
}

std::string data_parsing_server::parse_quant_cores_string(const std::string quant_cores_command) {
    std::string line;
    int quant_cores = -1;
    std::istringstream str(quant_cores_command);

    while (std::getline(str,line)){
        std::istringstream iss(line);
        int number;
        std::string label;

        while (iss >> label){
            if (label == ":"){
                break;
            }
        }

        iss >> number;
        if (quant_cores == -1){
            quant_cores = number;
        }
        break;
    }

    std::string add_ = "NumCores: ";
    std::string num_cores = std::to_string(quant_cores);
    num_cores.insert(0,add_);
    return num_cores;
}

std::string data_parsing_server::parse_cpu_freq_string(const std::string cpu_freq_command) {
    std::istringstream freq(cpu_freq_command);
    std::string line;
    int n = 0;
    double freq_avg = 0;

    while (std::getline(freq, line)) {
        std::istringstream iss(line);
        std::string temp;
        double value;
        n += 1;

        while (iss >> temp){
            if (temp == ":"){
                break;
            }
        }

        iss >> value;
        freq_avg += value;
    }
    freq_avg = freq_avg / n;

    std::string add_ = "MHz: ";
    std::string cpu_freq = std::to_string(freq_avg);
    cpu_freq.insert(0, add_);
    return cpu_freq;
}

std::vector<std::vector<long long>> data_parsing_server::read_cpu_info(const std::string cpu_string) { //for parseCpuLoadFile
    std::vector<std::vector<long long>> full_data;
    
    std::istringstream cpu(cpu_string);
    std::string line;

    while (std::getline(cpu, line)) {
        std::istringstream iss(line);
        std::string temp;
        long long value;
        std::vector<long long> cpu_data;

        iss >> temp;
        if (temp.find("cpu") == 0) {
            while (iss >> value) {
                cpu_data.push_back(value);
            }
            full_data.push_back(cpu_data);
        }
    }
    return full_data;
}

std::string data_parsing_server::parse_cpu_load_strings(const std::string cpu_load0, const std::string cpu_load1) {
    std::vector<double> cpuLoadClusters;

    auto data0 = read_cpu_info(cpu_load0);
    auto data5 = read_cpu_info(cpu_load1);

    for (size_t i = 0; i < data0.size(); i++) {
        long long idle0 = data0[i][3];
        long long total0 = data0[i][0] + data0[i][1] + data0[i][2] + data0[i][3];

        long long idle5 = data5[i][3];
        long long total5 = data5[i][0] + data5[i][1] + data5[i][2] + data5[i][3];

        double load = 1.0 - (double)(idle5 - idle0) / (total5 - total0);
        cpuLoadClusters.push_back(load);
    }
    std::string cpu_string = get_cpu_load_data(cpuLoadClusters);
    std::string add_ = "CpuLoads: ";
    cpu_string.insert(0, add_);
    return cpu_string;
}
