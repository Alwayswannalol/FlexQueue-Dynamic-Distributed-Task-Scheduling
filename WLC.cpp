#include<iostream>
#include<vector>
#include<limits>
using namespace std;

//веса характеристик в зависимости от типов задач
float weight_load = 0.3;
float weight_RAM = 0.2;
float weight_power = 0.5;

int WLC(const vector<int>& count_queue, const vector<float>& load_CPU, const vector<float>& RAM, const vector<float>& power_CPU, float max_RAM, float max_power_CPU) {
	float weight;
	float priority;
	float min_priority = numeric_limits<float>::infinity();
	int node = 0;
	for (int i = 0; i < load_CPU.size(); i++) {
		weight = weight_load * (load_CPU[i] / 100) + weight_RAM * (RAM[i] / max_RAM)	//вес узла = взвешенная сумма характеристик
			+ weight_power *(power_CPU[i] / max_power_CPU);

		priority = count_queue[i] / weight;
		
		if (priority < min_priority) { 
			min_priority = priority;
			node = i+1;
		}
	}
	return node;	//функция вовращает номер выбранного узла (начинается с 1)
}
