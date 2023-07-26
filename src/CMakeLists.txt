
# ====== Headers =======
set(HEADER_LIST
    "${MxBotLauncher_SOURCE_DIR}/include/mx/mx.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/application.hpp"
    "${MxBotLauncher_SOURCE_DIR}/include/mx/time.hpp"
)

# ======================


add_library(mxbotlib 
    ${HEADER_LIST}
    # Sources
    application.cpp
    entrypoint.cpp
)

target_include_directories(mxbotlib PUBLIC ../include)

find_package(OpenGL REQUIRED)
target_link_libraries(mxbotlib
PRIVATE
    glad
    glfw
    imgui
)

target_compile_features(mxbotlib PUBLIC cxx_std_17)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header files"
    FILES ${HEADER_LIST}
)