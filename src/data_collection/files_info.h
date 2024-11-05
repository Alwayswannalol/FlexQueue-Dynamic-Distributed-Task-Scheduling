#ifndef FILES_INFO_H
#define FILES_INFO_H

#include <fstream>
#include <string>

class files_info {
public:
    static int get_size(std::string filepath);
};

#endif //!FILES_INFO_H
