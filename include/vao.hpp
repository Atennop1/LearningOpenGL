#ifndef LEARNINGOPENGL_INCLUDE_VAO_HPP_
#define LEARNINGOPENGL_INCLUDE_VAO_HPP_

#include "glad/glad.h"
#include "vbo.hpp"

class VAO
{
public:
    explicit VAO();
    void LinkVBO(VBO VBO, GLuint layout);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint id_{};
};

#endif
