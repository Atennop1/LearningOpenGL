#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_PYRAMID_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_PYRAMID_VERTICES_HPP_

#include <glad/glad.h>

GLfloat pyramid_vertices[] =
{
    -0.5f, -0.4f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
    -0.5f, -0.4f, -0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
    0.5f, -0.4f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
    0.5f, -0.4f,  0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
    0.0f,  0.4f,  0.0f,     0.92f, 0.86f, 0.76f,     0.5f, 1.0f,
};

GLuint pyramid_indexes[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4,
};

#endif
