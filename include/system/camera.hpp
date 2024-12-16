#ifndef LEARNINGOPENGL_INCLUDE_SYSTEM_CAMERA_HPP_
#define LEARNINGOPENGL_INCLUDE_SYSTEM_CAMERA_HPP_

#include "shader.hpp"
#include "glm/vec3.hpp"
#include "GLFW/glfw3.h"

class Camera
{
public:
    Camera(int width, int height, glm::vec3 position);

    void Matrix(float FOV_degrees, float near_plane, float far_plane, Shader &shader, const char *uniform);
    void Inputs(GLFWwindow *window);

private:
    glm::vec3 position_{};
    glm::vec3 orientation_ = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

    int width_;
    int height_;

    float speed_ = 0.1f;
    float sensitivity_ = 200.0f;
    bool is_first_click = true;
};

#endif
