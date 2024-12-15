#ifndef LEARNINGOPENGL_INCLUDE_VAO_HPP_
#define LEARNINGOPENGL_INCLUDE_VAO_HPP_

#include "glad/glad.h"
#include "vbo.hpp"

class VAO
{
public:
    explicit VAO();
    void LinkAttributes(VBO &VBO, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void *offset);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint id_{};
};

#endif
