# == Glad ==
add_subdirectory(glad)

# == GLFW ==

if (!EMSCRIPTEN)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(glfw)
endif()

# == ImGui ==

add_subdirectory(imgui)

# == spdlog ==

add_subdirectory(spdlog)

# == yaml-cpp ==
add_subdirectory(yaml)