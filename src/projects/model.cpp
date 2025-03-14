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
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    auto camera = Camera();
    glfwSetWindowUserPointer(window, &camera);
    camera.Initialize(window, window_width, window_height, glm::vec3(-0.25f, -0.2f, 1.3f));

    auto model_shader = Shader("shaders/model/model.vert", "shaders/model/model.frag");
    auto outline_shader = Shader("shaders/model/outline.vert", "shaders/model/outline.frag");
    auto model = Model("media/model/scene.gltf");

    model_shader.Activate();
    glUniform3f(glGetUniformLocation(model_shader.GetID(), "light.ambient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(model_shader.GetID(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(model_shader.GetID(), "light.direction"), -0.2f, -1.0f, -0.3f);
    glUniform1f(glGetUniformLocation(model_shader.GetID(), "light.strength"), 1.0f);
    glUniform1f(glGetUniformLocation(model_shader.GetID(), "shininess"), 32.0f);

    outline_shader.Activate();
    glUniform1f(glGetUniformLocation(outline_shader.GetID(), "outline_thickness"), 0.01f);

    double previous_time = 0.0;
    double current_time = 0.0;
    double time_difference = 0.0;
    unsigned int counter = 0;

    while (!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        time_difference = current_time - previous_time;
        counter++;

        if (time_difference >= 1.0 / 30.0)
        {
            std::string FPS = std::to_string(int ((1.0 / time_difference) * counter));
            std::string ms = std::to_string((time_difference / counter) * 1000);
            std::string title = std::string("OpenGL - ").append(FPS).append("FPS / ").append(ms).append("ms");
            glfwSetWindowTitle(window, title.c_str());

            previous_time = current_time;
            counter = 0;
        }

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        camera.HandleInput(window);
        camera.UpdateMatrix(0.1f, 100.0f);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        model.Draw(model_shader, camera);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        model.Draw(outline_shader, camera);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    model_shader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
}
