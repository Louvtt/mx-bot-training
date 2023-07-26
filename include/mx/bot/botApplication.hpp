#ifndef _MX_BOT_BOTAPPLICATION_HPP_
#define _MX_BOT_BOTAPPLICATION_HPP_

#include "../application.hpp"

namespace mx {

class BotManager;

class BotApplication : public Application
{
private:
    BotManager* m_botManager;

public:
    BotApplication();
    ~BotApplication();

protected:
    void render() override;
    void update() override;
};

}


#endif //_MX_BOT_BOTAPPLICATION_HPP_