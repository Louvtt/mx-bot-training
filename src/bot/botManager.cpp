#include "mx/bot/botManager.hpp"

#include "mx/bot/bot.hpp"
#include "mx/fileUtils.hpp"

#include <cstdio>
#include <string.h>
#include <imgui.h>

#include "spdlog/spdlog.h"

#define BOT_PATH_SIZE 256

mx::BotManager::BotManager()
: m_bots(), 
m_selected(0),
m_botPath(new char[BOT_PATH_SIZE]())
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
        bot->update();
    }
}

void mx::BotManager::renderUI()
{
    ImGui::Begin("Bot Manager");
        ImGui::BeginGroup();
        ImGui::InputText("Path", m_botPath, BOT_PATH_SIZE);
        ImGui::SameLine();
        if(ImGui::Button("Add")) {
            addBot(std::string(m_botPath));
        }
        ImGui::EndGroup();

        // Bot list
        ImGui::BeginChild("Bots");
            int i = 0;
            for(auto [name, bot] : m_bots)
            {
                ImGui::Text("%02d Bot ", i);
                ImGui::SameLine();

                ImGui::BeginDisabled(!bot->canReload());
                if(ImGui::Button("Reload")) {
                    bot->reloadSymbols();
                }
                ImGui::EndDisabled();
                ++i;
            }
        ImGui::EndChild();
    ImGui::End();
}

void mx::BotManager::addBot(const std::string& path)
{   
    if(m_bots.find(path) == m_bots.end()) {
        if(mx::fileExists(path)) {
            m_bots.insert({ path, new Bot(path) });
        } else {
            spdlog::error("{} doesn't exists.", path);
        }
    } else {
        spdlog::error("{} already exists. (Use reload)", path);
    }
}