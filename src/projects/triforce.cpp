#include "projects/triforce.hpp"
#include "projects/triforce_vertices.hpp"
#include "system/shader.hpp"
#include "system/vbo.hpp"
#include "system/ebo.hpp"
#include "system/vao.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void TriforceProject::Activate() const
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

    auto shader = Shader("shaders/triforce/triforce.vert", "shaders/triforce/triforce.frag");
    GLint scale_uniform_ID = glGetUniformLocation(shader.GetID(), "scale");
    auto vao = VAO();
    vao.Bind();

    auto vbo = VBO(triforce_vertices, sizeof (triforce_vertices));
    auto ebo = EBO(triforce_indexes, sizeof (triforce_indexes));
    vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 6 * sizeof (float), (void*) nullptr);
    vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof (float), (void*)(3 * sizeof (float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Activate();
        glUniform1f(scale_uniform_ID, 1.0f);

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
