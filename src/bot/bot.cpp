#include "mx/bot/bot.hpp"

#include "mx/fileUtils.hpp"
#include <cstdio>
#include <spdlog/spdlog.h>

#if defined(_WIN32) | defined(WIN32)
#   error "Windows not supported yet."
#else
#   include <dlfcn.h>
#endif

mx::Bot::Bot(const std::string& name)
: m_path(name),
m_handle(nullptr),
m_symbols({
    nullptr
})
{
    loadSymbols();
}
mx::Bot::~Bot()
{
    #if defined(_WIN32) | defined(WIN32)
    #   error "Windows not supported yet."
    #else
        dlclose(m_handle);
    #endif
}

void mx::Bot::update()
{
    if(m_symbols.update != nullptr) {
        (*m_symbols.update)();
    }
}

void mx::Bot::loadSymbols()
{
    spdlog::info("Loading symbols for {}", m_path);
    m_lastLoadedMt = mx::getFileModifiedTimeSec(m_path);
    #if defined(_WIN32) | defined(WIN32)
    #   error "Windows not supported yet."
    #else
        m_handle = dlopen(m_path.c_str(), RTLD_NOW | RTLD_LOCAL);
        if(m_handle == nullptr) {
            perror("dlopen");
            return;
        }

        // load symbol
        m_symbols.update = *((Bot::bot_update*)dlsym(m_handle, "__update"));
        if(m_symbols.update == nullptr) {
            perror("dlsym");
            return;
        }

    #endif
}


bool mx::Bot::canReload() const
{
    int lastLoadedMt = mx::getFileModifiedTimeSec(m_path);
    if(lastLoadedMt != m_lastLoadedMt) {
        return true;
    }
    return false;
}

void mx::Bot::reloadSymbols()
{
    if(canReload()) {
        // clear symbols
        m_symbols.update = nullptr;

        // close handle
        dlclose(m_handle);
        m_handle = nullptr;

        // load again (will update lastLoadedMt)
        loadSymbols();
    }
}