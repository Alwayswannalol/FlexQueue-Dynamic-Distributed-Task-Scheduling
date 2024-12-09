#include "WLC.h"

//weights for characteristics depending on the types of tasks
float weight_load = 0.3;
float weight_RAM = 0.2;
float weight_power = 0.5;
int count_queue = 5;

/*
Example of the input string:
ID: 0.0.2323
CpuLoads: 0.134557 0.113402 0.104167 0.113402 0.342105
MemTotalKb: 8128072
MemFreeKb: 3188092
NumCores: 4
MHz: 2099.998000

ID: 0.0.1232141
CpuLoads: 0.134557 0.113402 0.104167 0.113402 0.342105
MemTotalKb: 8128072
MemFreeKb: 3188092
NumCores: 4
MHz: 2099.998000
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
	//reading values from the input string
	while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string temp;
        float value;

        iss >> temp;
        if (temp.find("ID:") == 0){ 
			iss >> temp;
            ID.push_back(temp);
        }
		else if (temp.find("CpuLoads:") == 0){ 
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
		weight = weight_load * (AVG_loadCPU[i] / 100) + weight_RAM * (RAM[i] / max_RAM)	//weight of the node = weighted sum of characteristics
			+ weight_power *(power_CPU[i] / max_powerCPU);
		//priority = count_queue[i] / weight;
		priority = count_queue / weight;

		if (priority < min_priority) { 
			min_priority = priority;
			node = ID[i];
		}
	}
	return node;	//function returns a ID of the choosing node
}

