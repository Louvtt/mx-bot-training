#include "mx/botlib/remoteBot.hpp"

RemoteBot::RemoteBot(const std::string& id)
: m_arena(nullptr),
m_name(id)
{}

void RemoteBot::setArena(mx::Arena* arena) {
    if(arena != nullptr) {
        m_arena = arena;
    }
}
mx::Arena* RemoteBot::getArena() const
{
    return m_arena;
}

std::string RemoteBot::getName() const
{
    return m_name;
}