#include "system/ebo.hpp"

EBO::EBO(const std::vector<GLuint> &indexes)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof (GLuint), indexes.data(), GL_STATIC_DRAW);
}

void EBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void EBO::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const
{
    glDeleteBuffers(1, &id_);
}
