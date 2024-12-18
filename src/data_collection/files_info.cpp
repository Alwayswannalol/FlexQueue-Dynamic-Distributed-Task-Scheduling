#include "files_info.h"

int files_info::get_size(std::string filepath) {
    std::fstream file(filepath);
    int size = 0;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    return size;
}

std::string files_info::get_filename(std::string filepath) {
    std::filesystem::path file_path(filepath);
    return file_path.filename().string();
}

std::string files_info::get_path(std::string filepath) {
    std::filesystem::path file_path(filepath);
    return file_path.parent_path().string();
}
