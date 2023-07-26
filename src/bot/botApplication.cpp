#include "mx/bot/botApplication.hpp"
#include "mx/bot/botManager.hpp"

mx::BotApplication::BotApplication()
: Application("MxBotLauncher"),
m_botManager(new BotManager())
{ }
mx::BotApplication::~BotApplication()
{
    delete m_botManager;
}

void mx::BotApplication::render()
{
    m_botManager->renderUI();
}
void mx::BotApplication::update()
{
    m_botManager->update();
}