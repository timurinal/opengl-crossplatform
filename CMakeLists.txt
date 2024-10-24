cmake_minimum_required(VERSION 3.29)
project(opengl_test)

set(CMAKE_CXX_STANDARD 20)

set(GLAD_PATH "external/glad")

add_subdirectory("external/glfw")
include_directories("external/glfw/include")

include_directories(${GLAD_PATH}/include)
include_directories("external/stb_image")
include_directories("external")

add_library(glad "${GLAD_PATH}/src/glad.c")

find_package(OpenGL REQUIRED)

if(UNIX)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
endif()

include_directories(src/includes)

add_executable(opengl_test src/main.cpp
        external/stb_image/stb_image.h
        src/includes/shader.h
        src/rendering/shader.cpp
)

if(UNIX)
    target_link_libraries(opengl_test glfw glad ${OPENGL_LIBRARIES} ${X11_LIBRARIES})
else()
    target_link_libraries(opengl_test glfw glad ${OPENGL_LIBRARIES})
endif()
