#ifndef _BOT_HPP_
#define _BOT_HPP_

#include <string>

namespace mx {
    class Arena;
}

/**
 * @brief Basic bot class
 */
class RemoteBot
{
private:
    mx::Arena* m_arena;
    std::string m_name;

public:
    RemoteBot(const std::string& id);
    virtual ~RemoteBot() = default;

    virtual void update() = 0;

    void setArena(mx::Arena* arena);
    mx::Arena* getArena() const;

    std::string getName() const;

    using bot_create_func = RemoteBot* (*)();
};

#endif //_BOT_HPP_