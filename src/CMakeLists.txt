
# ====== Headers =======
set(HEADER_LIST
    "${MxBotLauncher_SOURCE_DIR}/include/mx/mx.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/application.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/time.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/fileUtils.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/fileInput.hpp"
    # Core
    "${MxBotLauncher_SOURCE_DIR}/include/mx/core/platform.hpp"
    # Bot
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/bot.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/botManager.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/bot/botApplication.hpp"
)

# ======================


add_library(mxbotlib 
    ${HEADER_LIST}
    # Sources
    application.cpp
    entrypoint.cpp
    fileUtils.cpp
    fileInput.cpp

    bot/bot.cpp
    bot/botManager.cpp
    bot/botApplication.cpp
)

target_include_directories(mxbotlib PUBLIC ../include)

find_package(OpenGL REQUIRED)
target_link_libraries(mxbotlib
PRIVATE
    glad
    imgui
    yaml-cpp
    spdlog
    stdc++fs
)

target_compile_features(mxbotlib PUBLIC cxx_std_17)

# GLFW with EMSCRIPEN 
if(EMSCRIPTEN)
    target_link_options(mxbotlib PRIVATE -sUSE_GLFW=3)
else()
    target_link_libraries(mxbotlib PRIVATE glfw)
endif()

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header files"
    FILES ${HEADER_LIST}
)