cmake_minimum_required(VERSION 3.25)

project(Renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(renderer
    src/main.cpp
    external/glad/src/gl.c
)

target_include_directories(renderer
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/glad/include
)

target_link_libraries(renderer 
    PRIVATE 
        glfw
        OpenGL::GL
)
