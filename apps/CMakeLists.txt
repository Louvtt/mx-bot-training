
add_executable(mxlauncher launcher.cpp)
target_compile_features(mxlauncher PRIVATE cxx_std_17)

target_link_libraries(mxlauncher 
PRIVATE 
    mxbotlib
    glfw
    imgui
)