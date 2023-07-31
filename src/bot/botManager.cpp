#include "mx/bot/botManager.hpp"

#include "mx/bot/bot.hpp"
#include "mx/fileInput.hpp"
#include "mx/fileUtils.hpp"
#include "mx/core/platform.hpp"

#include <cstdio>
#include <string.h>
#include <imgui.h>

#include "spdlog/spdlog.h"

#define BOT_PATH_SIZE 256

mx::BotManager::BotManager()
: m_bots(), 
m_selected(""),
m_fileInput()
{ }

mx::BotManager::~BotManager()
{
    for(auto [name, bot]: m_bots) {
        delete bot;
    }
    m_bots.clear();
}

void mx::BotManager::update()
{
    for(auto [name, bot] : m_bots) {
        if(!bot->isPaused()) {
            bot->update();
        }
    }
}

static bool isEntryValid(char* entry)
{
    if (strlen(entry) == 0) return false;
    for(int i = 0; i < strlen(entry); ++i) {
        if(entry[i] != ' ') return true;
    }
    return false;
}

void mx::BotManager::renderUI()
{
    ImGui::SetNextWindowPos(ImVec2{0, 0});
    ImGui::SetNextWindowSize({300.f, ImGui::GetIO().DisplaySize.y});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
    ImGui::Begin("Bot Manager", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration);
    
    {
        if(m_fileInput.draw()) {
            addBot(m_fileInput.getFilePath());
        }
    }

    ImGui::Separator();

    // Bot List
    {
        ImGui::BeginChild("Bots", ImVec2(100, 0), true);
        int i = 0;
        for (auto [name, bot] : m_bots)
        {
            char label[128];
            std::snprintf(label, 128, "Bot %4d", i);
            if (ImGui::Selectable(label, m_selected == name, ImGuiSelectableFlags_AllowDoubleClick)) {
                spdlog::info("Selected {}", m_selected);
                m_selected = name;
            }
            ++i;
        }
        ImGui::EndChild();
    }
    ImGui::SameLine();
    {
        ImGui::BeginChild("Bot properties", ImVec2(200, 0), false);
        if(m_bots.find(m_selected) != m_bots.end()) {
            Bot* bot = m_bots.at(m_selected);
            ImGui::Text("Library Path: %s", bot->getPath().c_str());
            
            ImGui::BeginDisabled(!bot->canReload());
            if(ImGui::Button("Reload", ImVec2(-5, 0))) {
                bot->reloadSymbols();
            }
            ImGui::EndDisabled();

            if(ImGui::Button(bot->isPaused() ? "Play" : "Stop", ImVec2(-5, 0))) {
                bot->setPaused(!bot->isPaused());
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void mx::BotManager::addBot(const std::string& path)
{   
    if(m_bots.find(path) == m_bots.end()) {
        if(isPathValidLibrary(path)) {
            m_bots.insert({ path, new Bot(path) });
        }  else {
            spdlog::error("{} isn't a valid file (doesn't exist or wrong extension).", path);
        }
    } else {
        spdlog::error("{} already exists. (Use reload)", path);
    }
}

bool mx::BotManager::isPathValidLibrary(const std::string& path)
{
    if(mx::exists(path) && mx::isFile(path)) {
        #if defined(_WIN32) | defined(WIN32)
        if(mx::getFileExtension(path) == ".dll")
        #elif defined(__unix__)
        if(mx::getFileExtension(path) == ".so")
        #endif
        {
            return true;
        }
    }
   return false; 
}