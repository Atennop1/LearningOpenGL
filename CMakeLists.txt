cmake_minimum_required(VERSION 3.25)
project(LearningOpenGL)
set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL
        src/main.cpp
        libs/lib/glad/glad.c
        libs/lib/stb/std_image.c
        src/system/shader.cpp
        include/system/shader.hpp
        include/system/utils.hpp
        src/system/vbo.cpp
        include/system/vbo.hpp
        src/system/ebo.cpp
        include/system/ebo.hpp
        src/system/vao.cpp
        include/system/vao.hpp
        include/projects/triforce.hpp
        src/projects/triforce.cpp
        src/projects/cube.cpp
        include/projects/cube.hpp)

include_directories(${CMAKE_SOURCE_DIR}/libs/include include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/lib/glfw/libglfw3.a)
