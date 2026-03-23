cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

# -------- Automatically collect files --------

# All source files
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# All header files
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/headers/*.h
)

# -------- GLAD --------

add_library(glad glad/src/glad.c)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/glad/include
)

# -------- ImGui --------

add_library(imgui
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/backends/imgui_impl_glfw.cpp
    src/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_SOURCE_DIR}/headers/imgui
    ${CMAKE_SOURCE_DIR}/src/imgui/backends
)

# -------- Executable --------

add_executable(opengl_app
    ${SRC_FILES}
    ${HEADER_FILES}
)

# Include directories for headers
target_include_directories(opengl_app PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/headers/imgui
    ${CMAKE_SOURCE_DIR}/src/imgui/backends
    ${CMAKE_SOURCE_DIR}/glad/include
)

# Link libraries
target_link_libraries(opengl_app
    glad
    glfw
    GL
    imgui
)

# -------- Copy shaders automatically --------

file(GLOB SHADERS
    ${CMAKE_SOURCE_DIR}/resources/shaders/*
)

file(COPY ${SHADERS}
     DESTINATION ${CMAKE_BINARY_DIR}/shaders)