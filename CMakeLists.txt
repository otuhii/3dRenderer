cmake_minimum_required(VERSION 3.25)

project(Renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(external/glm)

add_executable(renderer
    external/stb-image/src/stb_image.cpp
    external/glad/src/gl.c
    src/main.cpp
    src/Parser.cpp
)

target_include_directories(renderer
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/stb-image/include
)

target_link_libraries(renderer 
    PRIVATE 
        glfw
        OpenGL::GL
        glm::glm
)
