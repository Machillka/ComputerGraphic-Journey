cmake_minimum_required(VERSION 3.20)
project(cg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ensure paths are absolute relative to this CMakeLists
set(EXTERN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# glad (single C source)
add_library(glad STATIC ${EXTERN_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${EXTERN_DIR}/glad/include)

# glfw: prefer subdirectory if present, otherwise try to find a system package
if(EXISTS "${EXTERN_DIR}/glfw/CMakeLists.txt")
    add_subdirectory(${EXTERN_DIR}/glfw)
else()
    find_package(glfw3 QUIET)
    # On some installs the target is glfw or glfw3 or GLFW::GLFW; we will handle below.
endif()

# glm (header-only)
if(EXISTS "${EXTERN_DIR}/glm/CMakeLists.txt")
    add_subdirectory(${EXTERN_DIR}/glm)
else()
    find_package(glm QUIET) # optional: system-installed glm
endif()

# main executable
# add_executable(cg src/main.cpp)
add_executable(cg src/z_buffer.cpp src/utilities/utilities.cpp)

# Link libraries: check which glfw/glm targets exist and link appropriately
if(TARGET glfw)                    # typical when using GLFW source subdir
    target_link_libraries(cg PRIVATE glad glfw)
elseif(TARGET glfw3)                # sometimes target is glfw3
    target_link_libraries(cg PRIVATE glad glfw3)
elseif(TARGET GLFW::GLFW)          # imported target from find_package
    target_link_libraries(cg PRIVATE glad GLFW::GLFW)
elseif(TARGET glfw_shared OR TARGET glfw_static)
    target_link_libraries(cg PRIVATE glad glfw_static)
else()
    message(FATAL_ERROR "GLFW not found or built. Add external/glfw as a submodule or install GLFW.")
endif()

# glm target name varies: prefer glm::glm, then glm, else nothing (glm is header-only)
if(TARGET glm::glm)
    target_link_libraries(cg PRIVATE glm::glm)
elseif(TARGET glm)
    target_link_libraries(cg PRIVATE glm)
endif()

# Windows / MSVC compile options
if(MSVC)
    target_compile_options(cg PRIVATE /W4 /permissive-)
endif()

# Useful: show summary
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "Using glad target: ${glad}")
