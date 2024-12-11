#ifndef LEARNINGOPENGL_INCLUDE_EBO_HPP_
#define LEARNINGOPENGL_INCLUDE_EBO_HPP_

#include "glad/glad.h"

class EBO
{
public:
    EBO(GLuint *indexes, GLsizeiptr size);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint id_{};
};

#endif
