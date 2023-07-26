
# ====== Headers =======
set(HEADER_LIST
    "${MxBotLauncher_SOURCE_DIR}/include/mx/mx.hpp"
)

# ======================

add_library(mxbotlib 
    # Sources
    ${HEADER_LIST}
)

target_include_directories(mxbotlib PUBLIC ../include)

target_link_libraries(mxbotlib
PRIVATE 
    glfw
    imgui
)

target_compile_features(mxbotlib PUBLIC cxx_std_17)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header files"
    FILES ${HEADER_LIST}
)