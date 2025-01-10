#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_SPACE_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_SPACE_VERTICES_HPP_

#include <glad/glad.h>

GLfloat space_pyramid_vertices[] =
{ //     COORDINATES    /        COLORS       /    TexCoord    /        NORMALS
   -0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,     0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
   -0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,     0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,     1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

   -0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,     0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
   -0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
    0.0f, 0.8f,  0.0f,     0.0f, 0.0f, 0.0f,     0.5f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side

   -0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
    0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,     0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
    0.0f, 0.8f,  0.0f,     0.0f, 0.0f, 0.0f,     0.5f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

    0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,     0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
    0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
    0.0f, 0.8f,  0.0f,     0.0f, 0.0f, 0.0f,     0.5f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side

    0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,     1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
   -0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,     0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
    0.0f, 0.8f,  0.0f,     0.0f, 0.0f, 0.0f,     0.5f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

GLuint space_pyramid_indexes[] =
{
    0,  1,  2,
    0,  2,  3,
    4,  6,  5,
    7,  9,  8,
    10, 12, 11,
    13, 15, 14
};

GLfloat space_lamp_vertices[] =
{
   -0.05f, -0.05f,  0.05f,
   -0.05f, -0.05f, -0.05f,
    0.05f, -0.05f, -0.05f,
    0.05f, -0.05f,  0.05f,
   -0.05f,  0.05f,  0.05f,
   -0.05f,  0.05f, -0.05f,
    0.05f,  0.05f, -0.05f,
    0.05f,  0.05f,  0.05f
};

GLuint space_lamp_indexes[] =
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
