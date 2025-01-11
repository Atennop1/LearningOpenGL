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
    camera.Initialize(window, window_width, window_height, glm::vec3(0.0f, 0.0f, 3.0f));

    auto cube_shader = Shader("shaders/space/cube.vert", "shaders/space/cube.frag");
    GLint cube_model_matrix_uniform_ID = glGetUniformLocation(cube_shader.GetID(), "model_matrix");
    GLint cube_light_position_uniform_ID = glGetUniformLocation(cube_shader.GetID(), "light.position");
    GLint cube_camera_position_uniform_ID = glGetUniformLocation(cube_shader.GetID(), "camera_position");

    cube_shader.Activate();
    glUniform1f(glGetUniformLocation(cube_shader.GetID(), "scale"), 1.0f);
    glUniform1f(glGetUniformLocation(cube_shader.GetID(), "material.shininess"), 64.0f);
    glUniform3f(glGetUniformLocation(cube_shader.GetID(), "light.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(cube_shader.GetID(), "light.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(cube_shader.GetID(), "light.linear"), 0.09f);
    glUniform1f(glGetUniformLocation(cube_shader.GetID(), "light.quadratic"), 0.032f);

    auto cube_texture = Texture("media/space/container.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    cube_texture.Activate(cube_shader, "tex0", 0);
    cube_texture.Activate(cube_shader, "material.diffuse", 0);
    cube_texture.Bind();

    auto cube_specular_texture = Texture("media/space/container_specular.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
    cube_specular_texture.Activate(cube_shader, "material.specular", 1);
    cube_specular_texture.Bind();

    auto cube_vao = VAO();
    auto cube_vbo = VBO(space_cube_vertices, sizeof (space_cube_vertices));
    auto cube_ebo = EBO(space_cube_indexes, sizeof (space_cube_indexes));

    cube_vao.LinkAttributes(cube_vbo, 0, 3, GL_FLOAT, 8 * sizeof (float), (void*) nullptr);
    cube_vao.LinkAttributes(cube_vbo, 1, 3, GL_FLOAT, 8 * sizeof (float), (void*)(3 * sizeof (float)));
    cube_vao.LinkAttributes(cube_vbo, 2, 2, GL_FLOAT, 8 * sizeof (float), (void*)(6 * sizeof (float)));

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

        auto light_color = glm::vec3(sin(glfwGetTime() * 2.0f), abs(sin(glfwGetTime() * 0.7f)), sin(glfwGetTime() * 1.3f));
        auto light_ambient = light_color * glm::vec3(0.2f);
        auto light_diffuse = light_color * glm::vec3(0.5f);
        auto light_position = glm::vec3(1.0f * sin(glfwGetTime()), 0.0f, 1.0f * cos(glfwGetTime()));
        auto light_model_matrix = glm::translate(glm::mat4(1.0f), light_position);

        double current_time = glfwGetTime();
        if (current_time - previous_time >= (1.0f / 60.0f))
        {
            rotation += 1.0f;
            previous_time = current_time;
        }

        auto cube_model_matrix = glm::mat4(1.0f);
        cube_model_matrix = glm::rotate(cube_model_matrix, glm::radians(-rotation), glm::vec3(1.0f, 0.0f, 0.0f));

        cube_vao.Bind();
        cube_shader.Activate();
        camera.DisplayMatrix(cube_shader, "camera_matrix");
        glUniformMatrix4fv(cube_model_matrix_uniform_ID, 1, GL_FALSE, glm::value_ptr(cube_model_matrix));
        glUniform3f(cube_light_position_uniform_ID, light_position.x, light_position.y, light_position.z);
        glUniform3f(cube_camera_position_uniform_ID, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(cube_shader.GetID(), "light.ambient"), light_ambient.x, light_ambient.y, light_ambient.z);
        glUniform3f(glGetUniformLocation(cube_shader.GetID(), "light.diffuse"), light_diffuse.x, light_diffuse.y, light_diffuse.z);
        glDrawElements(GL_TRIANGLES, sizeof(space_cube_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        lamp_vao.Bind();
        lamp_shader.Activate();
        camera.DisplayMatrix(lamp_shader, "camera_matrix");
        glUniformMatrix4fv(lamp_model_matrix_uniform_ID, 1, GL_FALSE, glm::value_ptr(light_model_matrix));
        glUniform3f(lamp_light_color_uniform_ID, light_color.x, light_color.y, light_color.z);
        glDrawElements(GL_TRIANGLES, sizeof(space_lamp_indexes) / sizeof(int), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube_vao.Delete();
    cube_vbo.Delete();
    cube_ebo.Delete();
    cube_shader.Delete();
    cube_texture.Delete();

    lamp_vao.Delete();
    lamp_vbo.Delete();
    lamp_ebo.Delete();
    lamp_shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}