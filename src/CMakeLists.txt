
# ====== Headers =======
set(HEADER_LIST
    "${MxBotLauncher_SOURCE_DIR}/include/mx/mx.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/fileUtils.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/fileInput.hpp"
    # Core
    "${MxBotLauncher_SOURCE_DIR}/include/mx/core/application.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/core/platform.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/core/time.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/core/log.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/core/console.hpp"
    # Bot
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/bot.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/arena.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/botManager.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/botApplication.hpp"
    # BotLib
    "${MxBotLauncher_SOURCE_DIR}/include/mx/botlib/remoteBot.hpp"
)

# ======================


add_library(mxbotlib
    ${HEADER_LIST}
    # Sources
    core/application.cpp
    core/entrypoint.cpp
    core/console.cpp
    fileUtils.cpp
    fileInput.cpp

    bot/bot.cpp
    bot/botManager.cpp
    bot/botApplication.cpp
    bot/arena.cpp

    botlib/remoteBot.cpp
)

target_include_directories(mxbotlib PUBLIC "${MxBotLauncher_SOURCE_DIR}/include")

target_link_libraries(mxbotlib
PUBLIC
    glad
    imgui
    yaml-cpp
    spdlog
    stdc++fs
)

target_compile_features(mxbotlib PUBLIC cxx_std_17)

# -fPIC
set_property(TARGET mxbotlib PROPERTY POSITION_INDEPENDENT_CODE ON)

# GLFW with EMSCRIPEN 
if(EMSCRIPTEN)
    target_link_options(mxbotlib PUBLIC -sUSE_GLFW=3)
else()
    target_link_libraries(mxbotlib PUBLIC glfw)
endif()

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header files"
    FILES ${HEADER_LIST}
)