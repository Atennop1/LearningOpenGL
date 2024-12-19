#include "projects/space.hpp"
#include "system/shader.hpp"
#include "system/vbo.hpp"
#include "system/ebo.hpp"
#include "system/vao.hpp"
#include "stb/stb_image.h"
#include "system/texture.hpp"
#include "system/camera.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void SpaceProject::Activate() const
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
    auto camera = Camera(window_width, window_height, glm::vec3(0.0f, 0.5f, 2.0f));

    GLfloat pyramid_vertices[] =
    {
       -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
       -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
        0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
        0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
        0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     0.5f, 1.0f,
    };

    GLuint pyramid_indexes[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,
    };

    auto pyramid_shader = Shader("shaders/space/space.vert", "shaders/space/space.frag");
    GLint pyramid_scale_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "scale");

    auto pyramid_texture = Texture("media/pyramid/medik.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    pyramid_texture.Activate(pyramid_shader, "tex0", 0);

    auto pyramid_vao = VAO();
    auto pyramid_vbo = VBO(pyramid_vertices, sizeof (pyramid_vertices));
    auto pyramid_ebo = EBO(pyramid_indexes, sizeof (pyramid_indexes));

    pyramid_vao.LinkAttributes(pyramid_vbo, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*)0);
    pyramid_vao.LinkAttributes(pyramid_vbo, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*)(3 * sizeof (float)));
    pyramid_vao.LinkAttributes(pyramid_vbo, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*)(6 * sizeof (float)));

    pyramid_vao.Unbind();
    pyramid_vbo.Unbind();
    pyramid_ebo.Unbind();

    GLfloat light_vertices[] =
    {
       -0.1f, -0.1f,  0.1f,
       -0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, -0.1f,
        0.1f, -0.1f,  0.1f,
       -0.1f,  0.1f,  0.1f,
       -0.1f,  0.1f, -0.1f,
        0.1f,  0.1f, -0.1f,
        0.1f,  0.1f,  0.1f
    };

    GLuint light_indexes[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };

    auto light_vao = VAO();
    auto light_vbo = VBO(light_vertices, sizeof (light_vertices));
    auto light_ebo = EBO(light_indexes, sizeof (light_indexes));

    light_vao.LinkAttributes(light_vbo, 0, 3, GL_FLOAT, 3 * sizeof (float), (void*)0);
    auto light_shader = Shader("shaders/space/light.vert", "shaders/space/light.frag");

    light_vao.Unbind();
    light_vbo.Unbind();
    light_ebo.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.SetMatrixInfo(45.0f, 0.1f, 100.0f);

        pyramid_vao.Bind();
        pyramid_texture.Bind();
        pyramid_shader.Activate();
        camera.DisplayMatrix(pyramid_shader, "camera_matrix");
        glUniform1f(pyramid_scale_uniform_ID, 1.0f);
        glDrawElements(GL_TRIANGLES, sizeof(pyramid_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        light_vao.Bind();
        light_shader.Activate();
        camera.DisplayMatrix(light_shader, "camera_matrix");
        glDrawElements(GL_TRIANGLES, sizeof(light_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    pyramid_vao.Delete();
    pyramid_vbo.Delete();
    pyramid_ebo.Delete();
    pyramid_shader.Delete();
    pyramid_texture.Delete();

    light_vao.Delete();
    light_vbo.Delete();
    light_ebo.Delete();
    light_shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}