cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME PixelEngine)
project(${PROJECT_NAME})


file(GLOB_RECURSE SHADERS
    "src/shaders/*.cpp"
    "src/shaders/*.h"
)
file(GLOB_RECURSE CORE
    "src/includes/*.cpp"
    "src/includes/*.h"
)

file(GLOB_RECURSE IMG
    "src/includes/img/*.cpp"
    "src/includes/img/*.h"
)

add_executable(${PROJECT_NAME} ${SHADERS} ${CORE} ${IMG} src/main.cpp)

source_group("shader"   FILES ${SHADERS})
source_group("core"     FILES ${CORE})
source_group("img"      FILES ${IMG})



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)
