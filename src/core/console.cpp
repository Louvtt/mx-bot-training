#include "mx/core/console.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ringbuffer_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <imgui.h>

#include <memory>

#include "mx/core/log.hpp"

mx::Console::Console() 
: m_maxDisplayedMessages(256)
{
    m_ringbufferSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(m_maxDisplayedMessages);
    m_ringbufferSink->set_pattern("[%^%l%$][%Y-%m-%d %H:%M:%S.%e] %v");
    auto consoleLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleLogger->set_pattern("[%^%l%$][%Y-%m-%d %H:%M:%S.%e] %v");

    std::vector<spdlog::sink_ptr> consoleSinks { m_ringbufferSink, consoleLogger };
    auto logger = std::make_shared<spdlog::logger>(MX_DEFAULT_LOGGER_NAME, consoleSinks.begin(), consoleSinks.end());
    logger->set_level(spdlog::level::trace); // all
    logger->flush_on(spdlog::level::trace);
    spdlog::register_logger(logger);
}

mx::Console::~Console() 
{
    spdlog::shutdown();
}

void mx::Console::Initialize()
{
    if(s_instance == nullptr) {
        s_instance = std::make_unique<mx::Console>();
        MX_INFO("Initialized logger");
    }
}

void mx::Console::Shutdown()
{
    if(s_instance != nullptr) {
        s_instance.reset();
    }
}

void mx::Console::DrawUI()
{
    auto size = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowSize(ImVec2(size.x - 300, 300));
    ImGui::SetNextWindowPos(ImVec2(300, 0));
    ImGui::Begin("Console");
    if(ImGui::BeginChild("ConsoleMessageView", ImVec2(-5, -5), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar)) {
        if(s_instance != nullptr) {
            for(auto message : s_instance->m_ringbufferSink->last_formatted(s_instance->m_maxDisplayedMessages))
            {
                ImGui::Text("%s", message.c_str());
            }
        } else {
            ImGui::Text("Console not initialized.");
        }
        ImGui::EndChild();
    }
    ImGui::End();
}