#include "mx/bot/arena.hpp"
#include "yaml-cpp/node/parse.h"

#include "mx/core/log.hpp"

#include <spdlog/spdlog.h>

mx::Arena::Arena()
: m_config(YAML::Load("assets/config.yaml"))
{ }
mx::Arena::~Arena()
{ }

void mx::Arena::logMessage(const std::string& message)
{
    MX_INFO("[Arena]: {}", message);
}