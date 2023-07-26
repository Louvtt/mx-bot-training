find_package(OpenGL REQUIRED)

add_library(glad 
STATIC
    include/glad/gl.h
    src/gl.c
)
target_include_directories(glad PUBLIC include)
target_link_libraries(glad
PRIVATE
    ${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)