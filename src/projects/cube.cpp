#include "projects/cube.hpp"
#include "system/shader.hpp"
#include "system/vbo.hpp"
#include "system/ebo.hpp"
#include "system/vao.hpp"
#include "stb/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void CubeProject::Activate() const
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
       -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
    };

    GLuint indexes[] =
    {
        0, 2, 1,
        0, 3, 2,
    };

    auto shader = Shader("shaders/cube/cube.vert", "shaders/cube/cube.frag");
    GLint scale_uniform_ID = glGetUniformLocation(shader.GetID(), "scale");
    GLint tex0_uniform_ID = glGetUniformLocation(shader.GetID(), "tex0");

    auto vao = VAO();
    auto vbo = VBO(vertices, sizeof (vertices));
    auto ebo = EBO(indexes, sizeof (indexes));

    vao.LinkAttributes(vbo, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*)0);
    vao.LinkAttributes(vbo, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*)(3 * sizeof (float)));
    vao.LinkAttributes(vbo, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*)(6 * sizeof (float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    int texture_width, texture_height, color_channels_number = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load("media/cube/medik.png", &texture_width, &texture_height, &color_channels_number, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float border_color[] = { 0.671f, 0.671f, 0.671f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(texture, 0);

    shader.Activate();
    glUniform1i(tex0_uniform_ID, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Activate();
        glUniform1f(scale_uniform_ID, 1.5f);

        vao.Bind();
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.Delete();
    glDeleteTextures(1, &texture);

    glfwDestroyWindow(window);
    glfwTerminate();
}