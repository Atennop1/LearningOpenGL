#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_TRIFORCE_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_TRIFORCE_VERTICES_HPP_

#include <glad/glad.h>
#include <cmath>

GLfloat triforce_vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f,
    0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f,
    0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    1.0f, 0.6f,  0.32f,
    -0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,    0.9f, 0.45f, 0.17f,
    0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,    0.9f, 0.45f, 0.17f,
    0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f,    0.8f, 0.3f,  0.02f,
};

GLuint triforce_indexes[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

#endif
