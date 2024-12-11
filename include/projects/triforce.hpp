#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_TRIFORCE_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_TRIFORCE_HPP_

#include "system/shader.hpp"
#include "system/vbo.hpp"
#include "system/ebo.hpp"
#include "system/vao.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void Activate()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    GLfloat vertices[] =
        {
            -0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f,
            0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f,
            0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    1.0f, 0.6f,  0.32f,
            -0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,    0.9f, 0.45f, 0.17f,
            0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,    0.9f, 0.45f, 0.17f,
            0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f,
        };

    GLuint indexes[] =
        {
            0, 3, 5,
            3, 2, 4,
            5, 4, 1
        };

    auto shader = Shader("shaders/default.vert", "shaders/default.frag");
    GLint scale_uniform_ID = glGetUniformLocation(shader.GetID(), "scale");
    auto vao = VAO();
    vao.Bind();

    auto vbo = VBO(vertices, sizeof (vertices));
    auto ebo = EBO(indexes, sizeof (indexes));
    vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 6 * sizeof (float), (void*)0);
    vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof (float), (void*)(3 * sizeof (float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Activate();
        glUniform1f(scale_uniform_ID, 0.5f);

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}


#endif
