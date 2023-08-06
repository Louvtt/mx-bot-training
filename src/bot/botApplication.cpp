#include "mx/bot/botApplication.hpp"
#include "imgui.h"
#include "mx/bot/arena.hpp"
#include "mx/bot/botManager.hpp"

mx::BotApplication::BotApplication()
: Application("MxBotLauncher"),
m_arena(new Arena()),
m_botManager(new BotManager(this))
{ }
mx::BotApplication::~BotApplication()
{
    delete m_botManager;
    delete m_arena;
}

void mx::BotApplication::render()
{
    m_botManager->renderUI();
}
void mx::BotApplication::update()
{
    m_botManager->update();
}

mx::Arena* mx::BotApplication::getArena()
{
    return m_arena;
}