#include <string>
#include <unistd.h>
#include <filesystem>
#include <fstream>
#include <sys/wait.h>
#include <vector>

namespace fs = std::filesystem;

class DataCollectionServer{
public:
    static std::string CmdExecuteRead(const char *command);
    static std::string CPULoadDataCollection();
    static std::string MemTotalDataCollection();
    static std::string MemFreeDataCollection();
    static std::string CoresDataCollection();
    static std::string FreqDataCollection();
};
