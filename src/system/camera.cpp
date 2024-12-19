#include "system/camera.hpp"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

Camera::Camera(int width, int height, glm::vec3 position)
{
    width_ = width;
    height_ = height;
    position_ = position;
}

void Camera::SetMatrixInfo(float FOV_degrees, float near_plane, float far_plane)
{
    glm::mat4 view_matrix = glm::mat4(1.0f);
    glm::mat4 projection_matrix = glm::mat4(1.0f);

    view_matrix = glm::lookAt(position_, position_ + orientation_, up_);
    projection_matrix = glm::perspective(glm::radians(FOV_degrees), float(width_) / float(height_), near_plane, far_plane);
    camera_matrix = projection_matrix * view_matrix;
}

void Camera::DisplayMatrix(Shader &shader, const char *uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), uniform), 1, GL_FALSE, glm::value_ptr(camera_matrix));
}

void Camera::Inputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position_ += speed_ * orientation_;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position_ += speed_ * -glm::normalize(glm::cross(orientation_, up_));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position_ += speed_ * -orientation_;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position_ += speed_ * glm::normalize(glm::cross(orientation_, up_));
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) position_ += speed_ * up_;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) position_ += speed_ * -up_;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed_ = 0.4f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed_ = 0.1f;

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
            is_first_click = false;
        }

        double mouse_x, mouse_y = 0.0;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwGetCursorPos(window, &mouse_x, &mouse_y);

        float rotation_x = sensitivity_ * float(mouse_y - ((float) height_ / 2)) / (float) height_;
        float rotation_y = sensitivity_ * float(mouse_x - ((float) height_ / 2)) / (float) height_;

        glm::vec3 new_orientation =
            glm::rotate(orientation_, glm::radians(-rotation_x), glm::normalize(glm::cross(orientation_, up_)));

        if (!((glm::angle(new_orientation, up_) <= glm::radians(5.0f))
            or glm::angle(new_orientation, -up_) <= glm::radians(5.0f)))
            orientation_ = new_orientation;

        orientation_ = glm::rotate(orientation_, glm::radians(-rotation_y), up_);
        glfwSetCursorPos(window, (float) width_ / 2, (float) height_ / 2);
    }
}
