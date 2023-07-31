#ifndef _MX_FILEUTILS_HPP_
#define _MX_FILEUTILS_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace mx {

bool exists(const std::string& path);
bool isFile(const std::string& path);
bool isDirectory(const std::string& path);

std::string getFileExtension(const std::string path);

uint32_t getFileModifiedTimeSec(const std::string& path);

struct EntryDescriptor {
    std::string path;
    std::string name;
    std::string extension;
    uint32_t mtime;
    uintmax_t size;
    bool isDir = false;
};
std::vector<EntryDescriptor> listDirectory(const std::string& path);


std::string getWorkingDirectoryPath();

}

#endif //_MX_FILEUTILS_HPP_