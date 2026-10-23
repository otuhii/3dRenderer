cmake_minimum_required(VERSION 3.20)

project(Renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


################################
##  OPENGL + external stuff
################################
find_package(OpenGL REQUIRED)

add_subdirectory(external)
###############################




set(RESOURCE_STAMP "${CMAKE_BINARY_DIR}/resources.stamp")
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

file(GLOB_RECURSE INTERNAL_HEADERS CONFIGURE_DEPENDS
        "include/*.h"
)

file(GLOB_RECURSE INTERNAL_SOURCES CONFIGURE_DEPENDS
        "source/*.cpp"
        "source/*.h"
)

file(GLOB_RECURSE EXTERNAL_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/gl.c"
)

file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS
        "${RESOURCE_DIR}/*"
)

list(APPEND ALL_SOURCE_FILES
        ${INTERNAL_HEADERS}
        ${INTERNAL_SOURCES}
        ${EXTERNAL_SOURCES}
)

add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})

###########################
add_custom_command(
        OUTPUT "${RESOURCE_STAMP}"
        DEPENDS ${RESOURCE_FILES}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR}
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
        COMMAND ${CMAKE_COMMAND} -E touch "${RESOURCE_STAMP}"
        COMMENT "Copying resource folder to output directory"
)
add_custom_target(
        copy_resources DEPENDS ${RESOURCE_STAMP}
)
add_dependencies(${PROJECT_NAME} copy_resources)
#####################################


target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include

)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glfw
        OpenGL::GL
        glm::glm
        stb
)
