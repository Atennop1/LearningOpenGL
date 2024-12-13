#include "system/vao.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &id_);
    Bind();
}

void VAO::LinkAttributes(VBO VBO, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void *offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() const
{
    glBindVertexArray(id_);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::Delete() const
{
    glDeleteVertexArrays(1, &id_);
}
