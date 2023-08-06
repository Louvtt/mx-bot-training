#ifndef _MX_CORE_CONSOLE_HPP_
#define _MX_CORE_CONSOLE_HPP_

#include <memory>
#include <spdlog/sinks/ringbuffer_sink.h>

namespace mx {

class Console
{
protected:

    inline static std::unique_ptr<Console> s_instance {nullptr}; 

    unsigned int m_maxDisplayedMessages {100};
    std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> m_ringbufferSink {nullptr};

public:
    Console();
    ~Console();

    static void Initialize();
    static void Shutdown();

    static void DrawUI();
};

}

#endif //_MX_CORE_CONSOLE_HPP_