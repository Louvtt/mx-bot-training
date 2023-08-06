#ifndef _MX_BOT_ARENA_HPP_
#define _MX_BOT_ARENA_HPP_

#include "yaml-cpp/node/node.h"
#include <string>

namespace mx {

class Arena
{
private:
    YAML::Node m_config;
    
public:
    Arena();
    ~Arena();

    void logMessage(const std::string& message);
};

}

#endif //_MX_BOT_ARENA_HPP_