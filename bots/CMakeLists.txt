cmake_minimum_required(VERSION 3.16)
project(BOTS 
    VERSION 0.1 
    DESCRIPTION "Bots script project (Allow building only bots)"
    LANGUAGES CXX C
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    # include mxbotlib
    # TODO: replace this line and fix how it works
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_BINARY_DIR}/mxbotlib")
endif()

add_subdirectory(src)

add_subdirectory(bot1)