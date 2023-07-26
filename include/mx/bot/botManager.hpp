#ifndef _MX_BOT_BOTMANAGER_HPP_
#define _MX_BOT_BOTMANAGER_HPP_

#include <unordered_map>
#include <string>

namespace mx {

class Bot;

class BotManager
{
private:
    std::unordered_map<std::string, Bot*> m_bots;

    // ui
    char* m_botPath;
    unsigned int m_selected;

public:
    BotManager();
    ~BotManager();

    void update();
    void renderUI();

    void addBot(const std::string& path);
};

}

#endif //_MX_BOTMANAGER_HPP_