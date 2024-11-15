#include "parsingServer.h"

std::string ServerInfo::getCpuLoadData(std::vector<double> cpuLoadClusters) {
    std::stringstream ss;
    for (size_t i = 0; i < cpuLoadClusters.size(); ++i) {
        if (i != 0) ss << " ";
        ss << cpuLoadClusters[i];
    }
    return ss.str();
}

std::string ServerInfo::parseMemTotalFile(const std::string memTotal) {
    unsigned long long memTotalKb;
    std::string label;

    std::istringstream str(memTotal);
    str >> label >> memTotalKb;

    std::string add_ = "MemTotalKb: ";
    std::string Total_ = std::to_string(memTotalKb);
    Total_.insert(0,add_);
    return Total_;
}

std::string ServerInfo::parseMemFreeFile(const std::string memFree) {
    unsigned long long memFreeKb;
    std::string label;

    std::istringstream str(memFree);
    str >> label >> memFreeKb;

    std::string add_ = "MemFreeKb: ";
    std::string Free_ = std::to_string(memFreeKb);
    Free_.insert(0,add_);
    return Free_;
}

std::string ServerInfo::parseCoresFile(const std::string Cores) {
    std::string line;
    int num_cores = -1;
    std::istringstream str(Cores);

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
        if (num_cores == -1){
            num_cores = number;
        }
        break;
    }

    std::string add_ = "NumCores: ";
    std::string Cores_ = std::to_string(num_cores);
    Cores_.insert(0,add_);
    return Cores_;
}

std::string ServerInfo::parseFreqAvg(const std::string FreqCPU) {
    std::istringstream Freq(FreqCPU);
    std::string line;
    int n = 0;
    double freq_avg = 0;

    while (std::getline(Freq, line)) {
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
    freq_avg = freq_avg/n;

    std::string add_ = "MHz: ";
    std::string Freq_ = std::to_string(freq_avg);
    Freq_.insert(0,add_);
    return Freq_;
}

std::vector<std::vector<long long>> ServerInfo::readCpuInfo(const std::string fileCPU) { //for parseCpuLoadFile
    std::vector<std::vector<long long>> fullData;
    
    std::istringstream file(fileCPU);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string temp;
        long long value;
        std::vector<long long> cpuData;

        iss >> temp;
        if (temp.find("cpu") == 0) {
            while (iss >> value) {
                cpuData.push_back(value);
            }
            fullData.push_back(cpuData);
        }
    }
    return fullData;
}

std::string ServerInfo::parseCpuLoadFile(const std::string cpuLoad0, const std::string cpuLoad1) {
    std::vector<double> cpuLoadClusters;

    auto data0 = readCpuInfo(cpuLoad0);
    auto data5 = readCpuInfo(cpuLoad1);

    for (size_t i = 0; i < data0.size(); i++) {
        long long idle0 = data0[i][3];
        long long total0 = data0[i][0] + data0[i][1] + data0[i][2] + data0[i][3];

        long long idle5 = data5[i][3];
        long long total5 = data5[i][0] + data5[i][1] + data5[i][2] + data5[i][3];

        double load = 1.0 - (double)(idle5 - idle0) / (total5 - total0);
        cpuLoadClusters.push_back(load);
    }
    std::string CPU_string = getCpuLoadData(cpuLoadClusters);
    std::string add_ = "CpuLoads: ";
    CPU_string.insert(0,add_);
    return CPU_string;
}

/*int main()
{
    ServerInfo test("");
    test.cpuInfoRuntimeData = test.parseCpuInfoRuntimeData("output_command_cpuinfo_runtime.txt");
    test.MEMFree = test.parseMemFreeFile("output_memfree_runtime.txt");
    test.cpuLoadClusters = test.parseCpuLoadFile("CPULoad0.txt", "CPULoad1.txt");

    std::cout << test.getCpuInfoRuntimeData() << std::endl;
    std::cout << test.getMaxFreq() << std::endl;
    std::cout << test.getMinFreq() << std::endl;
    std::cout << test.getMemFree() << std::endl;
    std::cout << test.getMemTotal() << std::endl;
    std::cout << test.getCpuLoadData() << std::endl;
}
*/