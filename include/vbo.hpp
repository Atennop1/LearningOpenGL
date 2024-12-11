#ifndef LEARNINGOPENGL_INCLUDE_VBO_HPP_
#define LEARNINGOPENGL_INCLUDE_VBO_HPP_

#include "glad/glad.h"

class VBO
{
public:
    VBO(GLfloat *vertices, GLsizeiptr size);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint id_{};
};

#endif
