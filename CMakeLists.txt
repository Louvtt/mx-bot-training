cmake_minimum_required(VERSION 3.16..3.20)

project(MxBotLauncher 
    VERSION 0.0.1 
    DESCRIPTION "A simple launcher to test bot scripts (for the exolegend event)"
    LANGUAGES CXX
)

option(MxBot_BUILD_DOCS "Build project documentation" OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set(CMAKE_CXX_EXTENSIONS OFF) # disable std=g++ and use std=c++
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Build docs
    if(BUILD_DOCS)
        find_package(Doxygen REQUIRED)
        if(DOXYGEN_FOUND)
            add_subdirectory(docs)
        else()
            message(STATUS "Doxygen not found, not building docs.")
        endif()
    endif()
endif()

# Add libraries
add_subdirectory(extern)

# Add sources
add_subdirectory(src)

# Add app
add_subdirectory(apps)