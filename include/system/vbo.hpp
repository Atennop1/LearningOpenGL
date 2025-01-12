#ifndef LEARNINGOPENGL_INCLUDE_VBO_HPP_
#define LEARNINGOPENGL_INCLUDE_VBO_HPP_

#include "vertex.hpp"
#include <glad/glad.h>
#include <vector>

class VBO
{
public:
    explicit VBO(const std::vector<Vertex> &vertices);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint id_{};
};

#endif
