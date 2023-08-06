#include "mx/fileUtils.hpp"
#include "mx/core/log.hpp"
#include "imgui.h"
#include <cmath>
#include <spdlog/spdlog.h>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

std::string mx::getFileExtension(const std::string path)
{
    return path.substr(path.find_last_of('.'));
}

bool mx::exists(const std::string& path)
{
    return fs::exists(path);
}

bool mx::isFile(const std::string& path) 
{
    return fs::is_regular_file(path)
        || fs::is_character_file(path)
        || fs::is_block_file(path);
}

bool mx::isDirectory(const std::string& path)
{
    return fs::is_directory(path);
}


uint32_t mx::getFileModifiedTimeSec(const std::string& path)
{
    if (fs::exists(path)) {
        return fs::last_write_time(path).time_since_epoch().count();
    }
    return 0;
}

std::vector<mx::EntryDescriptor> 
mx::listDirectory(const std::string& path)
{
    std::vector<mx::EntryDescriptor> listed{};
    if(fs::exists(path)) {
        MX_DEBUG("Listing {}", path);
        for(fs::directory_entry entry : fs::directory_iterator(path)) {
            listed.push_back(mx::EntryDescriptor{
                .path       = entry.path().string(),
                .name       = entry.path().filename().string(),
                .extension  = entry.path().extension().string(),
                .mtime      = (uint32_t)entry.last_write_time().time_since_epoch().count(),
                .size       = (entry.is_directory() ? 0u : entry.file_size()),
                .isDir      = entry.is_directory()
            });
        }
    }

    return listed;
}

std::string mx::getWorkingDirectoryPath()
{
    return fs::current_path().string();
}