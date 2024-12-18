#include "WLC.h"

//weights for characteristics depending on the types of tasks
float weight_load = 0.3;
float weight_RAM = 0.2;
float weight_power = 0.5;
//int count_queue = 5;

/*
Example of the input string:
0.0.0.0:50054
0.0.0.0:50052
0.0.0.0:50055
0.0.0.0:50053

CpuLoads: 0.109589 0.183486 0.0686275 0.149533 0.08 0.225 0.0784314 0.0980392 0.06 0.215686 0.020202 0.010101 0.1 MemFreeKb: 4875468 MHz: 933.266917 MemTotalKb: 16212660 NumCores: 6
CpuLoads: 0.0625 0.07 0.020202 0.0490196 0.09 0.04 0 0.039604 0.0808081 0.11 0.020202 0.010101 0.21 MemFreeKb: 4903948 MHz: 800.087833 MemTotalKb: 16212660 NumCores: 6
CpuLoads: 0.109677 0.183486 0.0686275 0.149533 0.08 0.225 0.0784314 0.0980392 0.0594059 0.217822 0.0204082 0.010101 0.1 MemFreeKb: 4874964 MHz: 865.284833 MemTotalKb: 16212660 NumCores: 6
CpuLoads: 0.0625521 0.07 0.020202 0.049505 0.09 0.04 0 0.039604 0.0808081 0.11 0.020202 0.010101 0.21 MemFreeKb: 4903948 MHz: 800.025500 MemTotalKb: 16212660 NumCores: 6
*/

std::string WLC(std::string DATA) {
	std::vector<std::string> ID;
	std::vector<float> AVG_loadCPU;
	std::vector<float> RAM;
	float max_RAM = 0;
	std::vector<float> num_cores;
	std::vector<float> AVG_MHz;

	std::istringstream file(DATA);
	std::string line;

	std::regex pattern_id(R"(\d{1,3}(?:\.\d{1,3}){3}:\d+)");
	//reading values from the input string
	while (std::getline(file, line)) {
		std::smatch match;

		if (std::regex_match(line, pattern_id)){
			ID.push_back(line);
		}
		else{
			std::istringstream iss(line);
        		std::string temp;
        		float value;

	        	while (iss >> temp){
				if (temp.find("CpuLoads:") == 0){ 
					iss >> value;
					AVG_loadCPU.push_back(value);
				}
				else if (temp.find("MemTotalKb:") == 0){ 
					iss >> value;
					if (value > max_RAM){max_RAM = value;}
				}
				else if (temp.find("MemFreeKb:") == 0){ 
					iss >> value;
					RAM.push_back(value);
				}
				else if (temp.find("NumCores:") == 0){ 
					iss >> value;
					num_cores.push_back(value);
				}
				else if(temp.find("MHz:") == 0){ 
					iss >> value;
					AVG_MHz.push_back(value);
				}
			}
			
		}
			
	}
	
	//calculation power CPU
	float max_powerCPU = 0;
	std::vector<float> power_CPU;
	for (int i = 0; i < ID.size(); i++){
		float power_node = AVG_MHz[i] * num_cores[i];
		power_CPU.push_back(power_node);
		if (power_node > max_powerCPU){max_powerCPU = power_node;}
	}

	float weight;
	float priority;
	float min_priority = std::numeric_limits<float>::infinity();
	std::string node;
	for (int i = 0; i < ID.size(); i++) {
		weight = weight_load * (AVG_loadCPU[i]) + weight_RAM * (RAM[i] / max_RAM)	//weight of the node = weighted sum of characteristics
			+ weight_power *(power_CPU[i] / max_powerCPU);
		//priority = count_queue[i] / weight;
		//priority = count_queue / weight;

		//up - used part of the CPU; down - weight * value of the free Mem
		priority = (1 - AVG_loadCPU[i]) / (weight * (RAM[i] / max_RAM)); // example: 0.1/(0.7 * 0.5) - free cpu=0.9, weight = 0.7, part of Memfree = 0.5
 
		if (priority < min_priority) { 
			min_priority = priority;
			node = ID[i];
		}
	}
	return node;	//function returns a ID of the choosing node
}
