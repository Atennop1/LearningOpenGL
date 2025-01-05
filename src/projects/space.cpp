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
    camera.Initialize(window, window_width, window_height, glm::vec3(0.0f, 0.5f, 3.0f));

    auto pyramid_shader = Shader("shaders/space/pyramid.vert", "shaders/space/pyramid.frag");
    GLint pyramid_scale_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "scale");
    GLint pyramid_model_matrix_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "model_matrix");
    GLint pyramid_light_color_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "light_color");
    GLint pyramid_light_position_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "light_position");
    GLint pyramid_camera_position_uniform_ID = glGetUniformLocation(pyramid_shader.GetID(), "camera_position");

    auto pyramid_texture = Texture("media/space/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    pyramid_texture.Activate(pyramid_shader, "tex0", 0);

    auto pyramid_vao = VAO();
    auto pyramid_vbo = VBO(space_pyramid_vertices, sizeof (space_pyramid_vertices));
    auto pyramid_ebo = EBO(space_pyramid_indexes, sizeof (space_pyramid_indexes));

    pyramid_vao.LinkAttributes(pyramid_vbo, 0, 3, GL_FLOAT, 11 * sizeof (float), (void*) nullptr);
    pyramid_vao.LinkAttributes(pyramid_vbo, 1, 3, GL_FLOAT, 11 * sizeof (float), (void*)(3 * sizeof (float)));
    pyramid_vao.LinkAttributes(pyramid_vbo, 2, 2, GL_FLOAT, 11 * sizeof (float), (void*)(6 * sizeof (float)));
    pyramid_vao.LinkAttributes(pyramid_vbo, 3, 3, GL_FLOAT, 11 * sizeof (float), (void*)(8 * sizeof (float)));

    auto lamp_vao = VAO();
    auto lamp_vbo = VBO(space_lamp_vertices, sizeof (space_lamp_vertices));
    auto lamp_ebo = EBO(space_lamp_indexes, sizeof (space_lamp_indexes));

    auto lamp_shader = Shader("shaders/space/lamp.vert", "shaders/space/lamp.frag");
    GLint lamp_model_matrix_uniform_ID = glGetUniformLocation(lamp_shader.GetID(), "model_matrix");
    GLint lamp_light_color_uniform_ID = glGetUniformLocation(lamp_shader.GetID(), "light_color");
    lamp_vao.LinkAttributes(lamp_vbo, 0, 3, GL_FLOAT, 3 * sizeof (float), (void*)nullptr);

    lamp_vao.Unbind();
    lamp_vbo.Unbind();
    lamp_ebo.Unbind();

    float rotation = 0.0f;
    double previous_time = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        camera.HandleInput(window);
        camera.UpdateMatrix(0.1f, 100.0f);

        auto light_color = glm::vec4(abs(sin(glfwGetTime())), abs(cos(glfwGetTime())), abs(sin(glfwGetTime())), 1.0f);
        auto light_position = glm::vec3(0.75f * sin(glfwGetTime()), 0.4f, 0.75f * cos(glfwGetTime()));
        auto light_model_matrix = glm::translate(glm::mat4(1.0f), light_position);

        double current_time = glfwGetTime();
        if (current_time - previous_time >= (1.0f / 60.0f))
        {
            rotation += 1.0f;
            previous_time = current_time;
        }

        auto pyramid_model_matrix = glm::mat4(1.0f);
        pyramid_model_matrix = glm::rotate(pyramid_model_matrix, glm::radians(-rotation), glm::vec3(0.0f, 1.0f, 0.0f));

        pyramid_vao.Bind();
        pyramid_texture.Bind();
        pyramid_shader.Activate();
        camera.DisplayMatrix(pyramid_shader, "camera_matrix");
        glUniform1f(pyramid_scale_uniform_ID, 1.0f);
        glUniformMatrix4fv(pyramid_model_matrix_uniform_ID, 1, GL_FALSE, glm::value_ptr(pyramid_model_matrix));
        glUniform4f(pyramid_light_color_uniform_ID, light_color.x, light_color.y, light_color.z, light_color.w);
        glUniform3f(pyramid_light_position_uniform_ID, light_position.x, light_position.y, light_position.z);
        glUniform3f(pyramid_camera_position_uniform_ID, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glDrawElements(GL_TRIANGLES, sizeof(space_pyramid_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        lamp_vao.Bind();
        lamp_shader.Activate();
        camera.DisplayMatrix(lamp_shader, "camera_matrix");
        glUniformMatrix4fv(lamp_model_matrix_uniform_ID, 1, GL_FALSE, glm::value_ptr(light_model_matrix));
        glUniform4f(lamp_light_color_uniform_ID, light_color.x, light_color.y, light_color.z, light_color.w);
        glDrawElements(GL_TRIANGLES, sizeof(space_lamp_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    pyramid_vao.Delete();
    pyramid_vbo.Delete();
    pyramid_ebo.Delete();
    pyramid_shader.Delete();
    pyramid_texture.Delete();

    lamp_vao.Delete();
    lamp_vbo.Delete();
    lamp_ebo.Delete();
    lamp_shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}