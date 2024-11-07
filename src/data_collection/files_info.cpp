#include "files_info.h"

int files_info::get_size(std::string filepath) {
    std::fstream file(filepath);
    int size = 0;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    return size;
}