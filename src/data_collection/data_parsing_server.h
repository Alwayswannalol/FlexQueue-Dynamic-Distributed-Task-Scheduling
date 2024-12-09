#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

class data_parsing_server {
public:
	static std::string parse_mem_free_string(const std::string mem_free_command);
	static std::string parse_quant_cores_string(const std::string quant_cores_command);
	static std::string parse_mem_total_string(const std::string mem_total_command);
	static std::string parse_cpu_freq_string(const std::string cpu_freq_command);
	static std::vector<std::vector<long long>> read_cpu_info(const std::string cpu_string);
	static std::string parse_cpu_load_strings(const std::string cpu_load0, const std::string cpu_load1);
	static std::string get_cpu_load_data(std::vector<double> cpu_load_clusters);
};
