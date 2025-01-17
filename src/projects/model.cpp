#include "projects/model.hpp"
#include "system/model.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void ModelProject::Activate() const
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
    camera.Initialize(window, window_width, window_height, glm::vec3(0.0f, 2.0f, 15.0f));

    auto shader = Shader("shaders/model/model.vert", "shaders/model/model.frag");
    auto model = Model("media/model/scene.gltf");
    shader.Activate();

    glUniform3f(glGetUniformLocation(shader.GetID(), "light.ambient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader.GetID(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shader.GetID(), "light.direction"), -0.2f, -1.0f, -0.3f);
    glUniform1f(glGetUniformLocation(shader.GetID(), "light.strength"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.GetID(), "shininess"), 32.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        camera.HandleInput(window);
        camera.UpdateMatrix(0.1f, 100.0f);
        model.Draw(shader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
}
