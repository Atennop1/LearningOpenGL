#include "system/camera.hpp"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

void Camera::Initialize(GLFWwindow *window, int width, int height, glm::vec3 position)
{
    width_ = width;
    height_ = height;
    position_ = position;

    last_frame = (float)glfwGetTime();
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x_position, double y_position) { ((Camera*)glfwGetWindowUserPointer(window))->MouseCallback(window, x_position, y_position); });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double x_offset, double y_offset) { ((Camera*)glfwGetWindowUserPointer(window))->ScrollCallback(window, x_offset, y_offset); });
}

void Camera::UpdateMatrix(float near_plane, float far_plane)
{
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);

    view_matrix = glm::lookAt(position_, position_ + orientation_, up_);
    projection_matrix = glm::perspective(glm::radians(fov_), float(width_) / float(height_), near_plane, far_plane);
    camera_matrix = projection_matrix * view_matrix;
}

void Camera::DisplayMatrix(const Shader &shader, const char *uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), uniform), 1, GL_FALSE, glm::value_ptr(camera_matrix));
}

void Camera::HandleInput(GLFWwindow *window)
{
    auto current_frame = (float)glfwGetTime();
    auto delta = current_frame - last_frame;
    last_frame = current_frame;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position_ += speed_ * delta * orientation_;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position_ += speed_ * delta * -glm::normalize(glm::cross(orientation_, up_));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position_ += speed_ * delta * -orientation_;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position_ += speed_ * delta * glm::normalize(glm::cross(orientation_, up_));
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) position_ += speed_ * delta * up_;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) position_ += speed_ * delta * -up_;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed_ = 12.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed_ = 3.0f;
}

void Camera::MouseCallback(GLFWwindow *window, double x_position, double y_position)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        is_first_click = true;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (is_first_click)
        {
            glfwSetCursorPos(window, (float) width_ / 2, (float) height_ / 2);
            x_position = (float) width_ / 2;
            y_position = (float) height_ / 2;
            is_first_click = false;
        }

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        float rotation_x = sensitivity_ * float(y_position - ((float) height_ / 2)) / (float) height_;
        float rotation_y = sensitivity_ * float(x_position - ((float) height_ / 2)) / (float) height_;

        glm::vec3 new_orientation = glm::rotate(orientation_, glm::radians(-rotation_x), glm::normalize(glm::cross(orientation_, up_)));
        if (!((glm::angle(new_orientation, up_) <= glm::radians(5.0f)) or glm::angle(new_orientation, -up_) <= glm::radians(5.0f)))
            orientation_ = new_orientation;

        orientation_ = glm::rotate(orientation_, glm::radians(-rotation_y), up_);
        glfwSetCursorPos(window, (float) width_ / 2, (float) height_ / 2);
    }
}

void Camera::ScrollCallback(GLFWwindow *window, double x_offset, double y_offset)
{
    fov_ -= (float)y_offset;

    if (fov_ < 5.0f)
        fov_ = 5.0f;

    if (fov_ > 60.0f)
        fov_ = 60.0f;
}

