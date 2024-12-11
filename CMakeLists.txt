cmake_minimum_required(VERSION 3.25)
project(LearningOpenGL)
set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL
        src/main.cpp
        src/glad.c
        src/shader.cpp
        include/shader.hpp
        include/utils.hpp
        src/vbo.cpp
        include/vbo.hpp
        src/ebo.cpp
        include/ebo.hpp src/vao.cpp include/vao.hpp)

include_directories(${CMAKE_SOURCE_DIR}/libs/include include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/lib/glfw/libglfw3.a)
