#include "projects/space.hpp"
#include "projects/space_vertices.hpp"
#include "system/shader.hpp"
#include "system/vbo.hpp"
#include "system/ebo.hpp"
#include "system/vao.hpp"
#include "stb/stb_image.h"
#include "system/texture.hpp"
#include "system/camera.hpp"
#include "glm/gtc/type_ptr.hpp"
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

    auto camera = Camera();
    glfwSetWindowUserPointer(window, &camera);
    camera.Initialize(window, window_width, window_height, glm::vec3(0.0f, 0.5f, 2.0f));

    auto pyramid_shader = Shader("shaders/space/space.vert", "shaders/space/space.frag");
    GLint pyramid_scale_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "scale");
    GLint pyramid_model_matrix_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "model_matrix");

    auto pyramid_texture = Texture("media/pyramid/medik.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    pyramid_texture.Activate(pyramid_shader, "tex0", 0);

    auto pyramid_vao = VAO();
    auto pyramid_vbo = VBO(space_pyramid_vertices, sizeof (space_pyramid_vertices));
    auto pyramid_ebo = EBO(space_pyramid_indexes, sizeof (space_pyramid_indexes));

    pyramid_vao.LinkAttributes(pyramid_vbo, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*) nullptr);
    pyramid_vao.LinkAttributes(pyramid_vbo, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*)(3 * sizeof (float)));
    pyramid_vao.LinkAttributes(pyramid_vbo, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*)(6 * sizeof (float)));

    pyramid_vao.Unbind();
    pyramid_vbo.Unbind();
    pyramid_ebo.Unbind();

    auto light_vao = VAO();
    auto light_vbo = VBO(space_light_vertices, sizeof (space_light_vertices));
    auto light_ebo = EBO(space_light_indexes, sizeof (space_light_indexes));

    auto light_shader = Shader("shaders/space/lamp.vert", "shaders/space/lamp.frag");
    GLint light_model_matrix_uniform_ID = glGetUniformLocation(light_shader.GetID(), "model_matrix");
    light_vao.LinkAttributes(light_vbo, 0, 3, GL_FLOAT, 3 * sizeof (float), (void*)nullptr);

    auto light_model = glm::mat4(1.0f);
    light_model = glm::translate(light_model, glm::vec3(-1.0f, 1.0f, -1.0f));

    light_vao.Unbind();
    light_vbo.Unbind();
    light_ebo.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        camera.HandleInput(window);
        camera.UpdateMatrix(0.1f, 100.0f);

        pyramid_vao.Bind();
        pyramid_texture.Bind();
        pyramid_shader.Activate();
        glUniform1f(pyramid_scale_uniform_ID, 1.0f);
        camera.DisplayMatrix(pyramid_shader, "camera_matrix");
        glUniformMatrix4fv(pyramid_model_matrix_uniform_ID, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        glDrawElements(GL_TRIANGLES, sizeof(space_pyramid_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        light_vao.Bind();
        light_shader.Activate();
        camera.DisplayMatrix(light_shader, "camera_matrix");
        glUniformMatrix4fv(light_model_matrix_uniform_ID, 1, GL_FALSE, glm::value_ptr(light_model));
        glDrawElements(GL_TRIANGLES, sizeof(space_light_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

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