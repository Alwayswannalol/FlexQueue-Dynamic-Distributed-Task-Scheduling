#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

class ServerInfo {
public:
	static std::string parseMemFreeFile(const std::string memFree);
	static std::string parseCoresFile(const std::string Cores);
	static std::string parseMemTotalFile(const std::string memTotal);
	static std::string parseFreqAvg(const std::string FreqCPU);
	static std::vector<std::vector<long long>> readCpuInfo(const std::string fileCPU);
	static std::string parseCpuLoadFile(const std::string cpuLoad0, const std::string cpuLoad1);
	static std::string getCpuLoadData(std::vector<double> cpuLoadClusters);
};
