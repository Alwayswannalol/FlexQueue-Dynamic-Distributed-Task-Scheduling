#include "WLC.h"

//weights for characteristics depending on the types of tasks
float weight_load = 0.3;
float weight_RAM = 0.2;
float weight_power = 0.5;

int WLC(const std::vector<int>& count_queue, const std::vector<float>& load_CPU, const std::vector<float>& RAM, const std::vector<float>& power_CPU, float max_RAM, float max_power_CPU) {
	float weight;
	float priority;
	float min_priority = std::numeric_limits<float>::infinity();
	int node = 0;
	for (int i = 0; i < load_CPU.size(); i++) {
		weight = weight_load * (load_CPU[i] / 100) + weight_RAM * (RAM[i] / max_RAM)	//weight of the node = weighted sum of characteristics
			+ weight_power *(power_CPU[i] / max_power_CPU);

		priority = count_queue[i] / weight;
		
		if (priority < min_priority) { 
			min_priority = priority;
			node = i+1;
		}
	}
	return node;	//function returns a number of the choosing node (starting from 1)
}
