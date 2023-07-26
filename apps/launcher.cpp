#include <iostream>
#include "mx/mx.hpp"
#include "mx/bot/botApplication.hpp"

mx::Application* createApplication(int argc, char **argv)
{
    return new mx::BotApplication();
}