#ifndef _MX_BOT_BOTMANAGER_HPP_
#define _MX_BOT_BOTMANAGER_HPP_

#include "../fileInput.hpp"
#include <unordered_map>
#include <string>

namespace mx {

class BotApplication;
class Bot;

class BotManager
{
private:
    std::unordered_map<std::string, Bot*> m_bots;

    // ui
    FileInput m_fileInput;
    std::string m_selected;

    BotApplication* m_application;
public:
    BotManager(BotApplication* application);
    ~BotManager();

    void update();
    void renderUI();

    void addBot(const std::string& path);

private:
    bool isPathValidLibrary(const std::string& path);
};

}

#endif //_MX_BOTMANAGER_HPP_