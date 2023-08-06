#ifndef _MX_BOT_BOTAPPLICATION_HPP_
#define _MX_BOT_BOTAPPLICATION_HPP_

#include "../core/application.hpp"

namespace mx {

class BotManager;
class Arena;

class BotApplication
: public Application
{
private:
    BotManager* m_botManager;
    Arena* m_arena;

public:
    BotApplication();
    ~BotApplication();

    Arena* getArena();

protected:
    void render() override;
    void update() override;
};

}


#endif //_MX_BOT_BOTAPPLICATION_HPP_