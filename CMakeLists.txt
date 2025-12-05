cmake_minimum_required(VERSION 3.20)
project(cg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_library(glfw STATIC)
target_include_directories(glfw PUBLIC external/glfw/include)

add_library(glm STATIC)
target_include_directories(glm PUBLIC external/glm/)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# 主程序
add_executable(cg src/main.cpp)

# 链接依赖
target_link_libraries(cg PRIVATE glad glfw glm)

# Windows 平台编译选项
if(MSVC)
    target_compile_options(cg PRIVATE /W4 /permissive-)
endif()
