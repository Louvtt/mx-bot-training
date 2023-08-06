#ifndef _MX_BOT_BOT_HPP_
#define _MX_BOT_BOT_HPP_

#include <cstdint>
#include <string>

#include "../botlib/remoteBot.hpp"
#include "arena.hpp"

namespace mx {

class Bot
{
private:
    std::string m_path;
    void* m_handle;

    struct symbols {
        RemoteBot::bot_create_func createFunc;
        RemoteBot* remoteBot;
    } m_symbols;

    uint32_t m_lastLoadedMt;

    struct Position {
        float x, y;
    } m_position;

    bool m_paused;

public:
    Bot(const std::string& path);
    ~Bot();

    void update();

    void loadSymbols();

    bool canReload() const;
    void reloadSymbols();

    bool isPaused() const;
    void setPaused(bool paused);

    void setArena(Arena* arena);

    std::string getPath() const;
};

}

#endif //_MX_BOT_HPP_