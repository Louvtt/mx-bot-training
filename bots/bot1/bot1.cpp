// #pragma once

#include "bot/types.hpp"
#include "mx/bot/arena.hpp"
#include "mx/botlib/remoteBot.hpp"
#include <iostream>

class BotTestOne
: public RemoteBot
{
private:
    // custom properties goes here ...
public:
    BotTestOne()
    : RemoteBot("BotOne")
    {
        // initialisation code goes here ...
    }

    void update() override
    {
        mx::Arena* arena = getArena();
        arena->logMessage("Bot Update method");
    }
};

REGISTER_BOT(BotTestOne);