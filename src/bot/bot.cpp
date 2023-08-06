#include "mx/bot/bot.hpp"

#include "mx/core/platform.hpp"
#include "mx/botlib/remoteBot.hpp"
#include "mx/fileUtils.hpp"
#include "mx/core/log.hpp"

#include <cerrno>
#include <cstdio>
#include <spdlog/spdlog.h>

#ifdef MX_WINDOWS
#   undef UNICODE
#   include <Windows.h>
/**
 * @brief Get the Last error window message
 * @return Description of the last WIN32 API error message
 * 
 * from: https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
*/
static std::string GetWindowsLastErrorDescription()
{
    DWORD errorMessageID = GetLastError();
    if(errorMessageID == 0) {
        return "Unknown error.";
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    LocalFree(messageBuffer);

    return message;
}
#elif defined(MX_LINUX)
#   include <dlfcn.h>
#endif

mx::Bot::Bot(const std::string& name)
: m_path(name),
m_handle(nullptr),
m_symbols({
    nullptr
}),
m_paused(true)
{
    loadSymbols();
}
mx::Bot::~Bot()
{
    #ifdef MX_WINDOWS
    FreeLibrary((HMODULE)m_handle);
    #else
        dlclose(m_handle);
    #endif
}

void mx::Bot::update()
{
    if(m_symbols.remoteBot != nullptr) {
        m_symbols.remoteBot->update();
    }
}

void mx::Bot::loadSymbols()
{
    MX_INFO("Loading symbols for {}", m_path);
    m_lastLoadedMt = mx::getFileModifiedTimeSec(m_path);
    #ifdef MX_WINDOWS
    HMODULE handle = LoadLibrary(m_path.c_str());
    m_handle = handle;
    if(m_handle == nullptr) {
        MX_ERROR("[LoadLibrary] : {}", GetWindowsLastErrorDescription());
        return;
    }

    m_symbols.createFunc = (RemoteBot::bot_create_func)GetProcAddress(handle, "createBot");
    if(m_symbols.createFunc == nullptr) {
        MX_ERROR("[GetProcAddress] : {}", GetWindowsLastErrorDescription());
        return;
    } else {
        m_symbols.remoteBot = (*m_symbols.createFunc)(); 
    }
    #else
        m_handle = dlopen(m_path.c_str(), RTLD_NOW | RTLD_LOCAL);
        if(m_handle == nullptr) {
            MX_ERROR("[dlopen] : {}", dlerror());
            return;
        }

        // load symbol
        m_symbols.createFunc = *((RemoteBot::bot_create_func*)dlsym(m_handle, "createBot"));
        if(m_symbols.createFunc == nullptr) {
            MX_ERROR("[dlsym] : {}", dlerror());
            return;
        } else {
            m_symbols.remoteBot = (*m_symbols.createFunc)(); 
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
        m_symbols.remoteBot = nullptr;

        // close handle
        #ifdef MX_WINDOWS
        FreeLibrary((HMODULE)m_handle);
        #else
        dlclose(m_handle);
        #endif
        m_handle = nullptr;

        // load again (will update lastLoadedMt)
        loadSymbols();
    }
}

std::string mx::Bot::getPath() const
{
    return m_path;
}

bool mx::Bot::isPaused() const
{
    return m_paused;
}
void mx::Bot::setPaused(bool paused)
{
    m_paused = paused;
}

void mx::Bot::setArena(Arena* arena)
{
    if(m_symbols.remoteBot != nullptr) 
    {
        m_symbols.remoteBot->setArena(arena);
    }
}