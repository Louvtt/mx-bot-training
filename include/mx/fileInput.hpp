/**
 * @file fileInput.hpp
 * @author Louvtt (louvttgames@gmail.com)
 * @brief Implement a wrapper for a file input with imgui <br/>
 * If you want to override the max file path size please define ``_MX_MAX_FILE_PATH``
 * @version 0.1
 * @date 2023-07-30
 * @copyright Copyright (c) 2023
 */

#ifndef _MX_FILEINPUT_HPP_
#define _MX_FILEINPUT_HPP_

#include "mx/fileUtils.hpp"
#include <string>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

namespace mx {

/**
 * @brief (ImGui) Widget for file input 
 */
class FileInput
{
private:
    std::string m_currentFilePathTemp;
    fs::path m_currentFilePath;
    std::string m_currentPathTemp;
    fs::path m_currentPath;

    std::string m_popup_id;
    bool m_modalOpened;
    std::vector<mx::EntryDescriptor> m_currentEntries;
public:
    FileInput();
    /**
     * @brief Draw the widget
     * @return if the open button is pressed
     */
    bool draw();

    /**
     * @brief Get the current file Path
     * @return const char* 
     */
    fs::path getFilePath() const;

    /**
     * @brief Set the current search path (must be a directory)
     * @param path current search path
     */
    void setCurrentPath(const std::string& path);
};

}

#endif //_MX_FILEINPUT_HPP_