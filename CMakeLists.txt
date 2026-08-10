cmake_minimum_required(VERSION 3.25)

project(Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(renderer
    src/main.cpp
)

target_link_libraries(renderer 
    PRIVATE 
        glfw
        OpenGL::GL
)
