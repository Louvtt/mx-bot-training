
find_package(OpenGL REQUIRED)

add_library(glad 
STATIC
    include/glad/gl.h
    src/gl.c
)
target_include_directories(glad PUBLIC include)