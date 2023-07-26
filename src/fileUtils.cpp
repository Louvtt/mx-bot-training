#include "mx/fileUtils.hpp"

#if defined(_WIN32) | defined(WIN32)
#   error "Windows not supported yet."
#else
#   include <sys/stat.h>
#endif


bool mx::fileExists(const std::string& path)
{
    struct stat fileStat;
    return (stat(path.c_str(), &fileStat)) == 0;
}

int mx::getFileModifiedTimeSec(const std::string& path)
{
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0) {
        return fileStat.st_mtim.tv_sec;
    }
    return 0;
}