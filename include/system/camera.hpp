#ifndef LEARNINGOPENGL_INCLUDE_SYSTEM_CAMERA_HPP_
#define LEARNINGOPENGL_INCLUDE_SYSTEM_CAMERA_HPP_

#include "shader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

class Camera
{
public:
    Camera() = default;
    void Initialize(GLFWwindow *window, int width, int height, glm::vec3 position);
    [[nodiscard]] glm::vec3 GetPosition() const { return position_; }

    void UpdateMatrix(float near_plane, float far_plane);
    void DisplayMatrix(const Shader &shader, const char *uniform);
    void HandleInput(GLFWwindow *window);

private:
    void MouseCallback(GLFWwindow *window, double x_position, double y_position);
    void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset);

    glm::vec3 position_{};
    glm::vec3 orientation_ = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 camera_matrix{};

    int width_{};
    int height_{};
    float last_frame{};

    float speed_ = 3.0f;
    float sensitivity_ = 200.0f;
    float fov_ = 45.0f;
    bool is_first_click = true;
};

#endif
