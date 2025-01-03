#include "projects/pyramid.hpp"
#include "system/shader.hpp"
#include "system/vbo.hpp"
#include "system/ebo.hpp"
#include "system/vao.hpp"
#include "stb/stb_image.h"
#include "system/texture.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void PyramidProject::Activate() const
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int window_width = 800;
    int window_height = 800;
    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "OpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);

    GLfloat vertices[] =
    {
       -0.5f, -0.4f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
       -0.5f, -0.4f, -0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
        0.5f, -0.4f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
        0.5f, -0.4f,  0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
        0.0f,  0.4f,  0.0f,     0.92f, 0.86f, 0.76f,     0.5f, 1.0f,
    };

    GLuint indexes[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,
    };

    auto shader = Shader("shaders/pyramid/pyramid.vert", "shaders/pyramid/pyramid.frag");
    GLint scale_uniform_ID = glGetUniformLocation(shader.GetID(), "scale");

    auto texture = Texture("media/pyramid/medik.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    texture.Activate(shader, "tex0", 0);

    auto vao = VAO();
    auto vbo = VBO(vertices, sizeof (vertices));
    auto ebo = EBO(indexes, sizeof (indexes));

    vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*)0);
    vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*)(3 * sizeof (float)));
    vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*)(6 * sizeof (float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    float rotation = 0.0f;
    double previous_time = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Activate();

        double current_time = glfwGetTime();
        if (current_time - previous_time >= (1.0f / 60.0f))
        {
            rotation += 1.0f;
            previous_time = current_time;
        }

        glm::mat4 model_matrix = glm::mat4(1.0f);
        glm::mat4 view_matrix = glm::mat4(1.0f);
        glm::mat4 projection_matrix = glm::mat4(1.0f);

        model_matrix = glm::rotate(model_matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -2.0f));
        projection_matrix = glm::perspective(glm::radians(45.0f), float(window_width) / float(window_height), 0.1f, 100.0f);

        GLint model_matrix_uniform_id = glGetUniformLocation(shader.GetID(), "model_matrix");
        glUniformMatrix4fv(model_matrix_uniform_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
        GLint view_matrix_uniform_id = glGetUniformLocation(shader.GetID(), "view_matrix");
        glUniformMatrix4fv(view_matrix_uniform_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
        GLint projection_matrix_uniform_id = glGetUniformLocation(shader.GetID(), "projection_matrix");
        glUniformMatrix4fv(projection_matrix_uniform_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        vao.Bind();
        texture.Bind();
        glUniform1f(scale_uniform_ID, 1.0f);
        glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.Delete();
    texture.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}