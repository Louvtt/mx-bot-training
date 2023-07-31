#include "mx/fileInput.hpp"

#include "mx/fileUtils.hpp"

#include <cstdlib>
#include <cstring>

#include <filesystem>
#include <spdlog/spdlog.h>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "spdlog/fmt/bundled/core.h"

constexpr const char* POPUP_FILE_ID_BASE = "Choose file##{}";
constexpr unsigned int RESERVED_STRING = 256; 

mx::FileInput::FileInput()
: m_modalOpened(false),
m_currentEntries(),
m_currentFilePath(),
m_currentPath()
{
    m_currentPathTemp.reserve(256);
    
    m_popup_id = fmt::format(POPUP_FILE_ID_BASE, rand());
    setCurrentPath(mx::getWorkingDirectoryPath());
}
bool mx::FileInput::draw()
{
    // Small input
    ImGui::BeginGroup();
        if(ImGui::Button("...")) {
            m_modalOpened = true;
        }
        ImGui::SameLine();
        if(ImGui::InputText("Path", &m_currentFilePathTemp, ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue)) {
            if(fs::exists(m_currentFilePathTemp)) {
                m_currentFilePath = m_currentPathTemp;
            }
        }
        bool openButton = ImGui::Button("Open");
    ImGui::EndGroup();


    // modal (centered)
    ImVec2 dSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowFocus();
    ImGui::SetNextWindowSize({dSize.x * .5f, dSize.y * .5f}, m_modalOpened);
    if(m_modalOpened) {
        if(ImGui::Begin(m_popup_id.c_str(), &m_modalOpened)) {
            {   // nav bar
                ImGui::BeginGroup();
                if(ImGui::InputText("Current Path", &m_currentPathTemp, ImGuiInputTextFlags_EnterReturnsTrue)) {
                    setCurrentPath(m_currentPathTemp);
                }
                ImGui::SameLine();
                if(ImGui::Button("Go")) {
                    setCurrentPath(m_currentPathTemp);
                }
                ImGui::EndGroup();
            }

            {   // file selection
                ImGui::BeginChild("Files", ImVec2(-2.f, -2.f), true);
                if(m_currentEntries.size() == 0) {
                    ImGui::Text("No files founds here.");
                }
                if(ImGui::Selectable("..", false, ImGuiSelectableFlags_AllowDoubleClick)) {
                    if(m_currentPath.has_parent_path()) {
                        setCurrentPath(m_currentPath.parent_path());
                    }
                }
                for(auto entry : m_currentEntries) {
                    if(ImGui::Selectable(entry.name.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
                        spdlog::info("{} selected", entry.name);
                        if(entry.isDir) {
                            setCurrentPath(entry.path);
                        } else {
                            m_currentPathTemp = entry.path;
                            m_currentFilePath = entry.path;
                            openButton = true;
                            m_modalOpened = false;
                        }
                    }
                }
                ImGui::EndChild();
            }
        }
        
        ImGui::End();
    }

    return openButton;
}

fs::path mx::FileInput::getFilePath() const
{
    return m_currentFilePath;
}

void mx::FileInput::setCurrentPath(const std::string& path)
{
    if(fs::exists(path)
    && fs::is_directory(path)) {
        spdlog::debug("[FileInput]: Setting path to {}", m_currentPathTemp);
        m_currentPath = path;
        m_currentEntries = mx::listDirectory(path);
    }
}