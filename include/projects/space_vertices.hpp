#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_SPACE_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_SPACE_VERTICES_HPP_

#include <glad/glad.h>

GLfloat space_pyramid_vertices[] =
{
   -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
   -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
    0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.0f,
    0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     1.0f, 0.0f,
    0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     0.5f, 1.0f,
};

GLuint space_pyramid_indexes[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4,
};

GLfloat space_light_vertices[] =
{
   -0.1f, -0.1f,  0.1f,
   -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f,  0.1f,
   -0.1f,  0.1f,  0.1f,
   -0.1f,  0.1f, -0.1f,
    0.1f,  0.1f, -0.1f,
    0.1f,  0.1f,  0.1f
};

GLuint space_light_indexes[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

#endif
