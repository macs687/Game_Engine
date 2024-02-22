cmake_minimum_required(VERSION 3.27.9 FATAL_ERROR)

set(PROJECT_NAME Game_Engine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    src/engine.cpp
    src/Render/ShaderProgram.cpp
    src/Render/ShaderProgram.h
    src/Math/Math.cpp
    src/Math/Math.h
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)