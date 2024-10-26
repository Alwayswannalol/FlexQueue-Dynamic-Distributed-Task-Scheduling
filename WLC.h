#pragma once
#ifndef WLC_H
#define WLC_H

#include<vector>

int WLC(const std::vector<int>& count_queue, const std::vector<float>& load_CPU, const std::vector<float>& RAM, const std::vector<float>& power_CPU, float max_RAM, float max_power_CPU);

#endif // !WLC_H