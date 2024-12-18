#ifndef FILES_INFO_H
#define FILES_INFO_H

#include <fstream>
#include <string>
#include <filesystem>

class files_info {
public:
    static int get_size(std::string filepath);
    static std::string get_filename(std::string filepath);
    static std::string get_path(std::string filepath);
};

#endif //!FILES_INFO_H
