#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_SPACE_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_SPACE_VERTICES_HPP_

#include "system/vertex.hpp"
#include <glad/glad.h>
#include <vector>

std::vector<Vertex> space_cube_vertices =
{
   { glm::vec3(-0.4f, -0.4f, -0.4f),    glm::vec3( 0.0f,  0.0f, -1.0f),     glm::vec2(0.0f,  0.0f) },
   { glm::vec3( 0.4f, -0.4f, -0.4f),    glm::vec3( 0.0f,  0.0f, -1.0f),     glm::vec2(1.0f,  0.0f) },
   { glm::vec3( 0.4f,  0.4f, -0.4f),    glm::vec3( 0.0f,  0.0f, -1.0f),     glm::vec2(1.0f,  1.0f) },
   { glm::vec3(-0.4f,  0.4f, -0.4f),    glm::vec3( 0.0f,  0.0f, -1.0f),     glm::vec2(0.0f,  1.0f) },

   { glm::vec3(-0.4f, -0.4f,  0.4f),    glm::vec3( 0.0f,  0.0f,  1.0f),     glm::vec2(0.0f,  0.0f) },
   { glm::vec3( 0.4f, -0.4f,  0.4f),    glm::vec3( 0.0f,  0.0f,  1.0f),     glm::vec2(1.0f,  0.0f) },
   { glm::vec3( 0.4f,  0.4f,  0.4f),    glm::vec3( 0.0f,  0.0f,  1.0f),     glm::vec2(1.0f,  1.0f) },
   { glm::vec3(-0.4f,  0.4f,  0.4f),    glm::vec3( 0.0f,  0.0f,  1.0f),     glm::vec2(0.0f,  1.0f) },

   { glm::vec3(-0.4f,  0.4f,  0.4f),    glm::vec3(-1.0f,  0.0f,  0.0f),     glm::vec2(1.0f,  0.0f) },
   { glm::vec3(-0.4f,  0.4f, -0.4f),    glm::vec3(-1.0f,  0.0f,  0.0f),     glm::vec2(1.0f,  1.0f) },
   { glm::vec3(-0.4f, -0.4f, -0.4f),    glm::vec3(-1.0f,  0.0f,  0.0f),     glm::vec2(0.0f,  1.0f) },
   { glm::vec3(-0.4f, -0.4f,  0.4f),    glm::vec3(-1.0f,  0.0f,  0.0f),     glm::vec2(0.0f,  0.0f) },

   { glm::vec3( 0.4f,  0.4f,  0.4f),    glm::vec3( 1.0f,  0.0f,  0.0f),     glm::vec2(1.0f,  0.0f) },
   { glm::vec3( 0.4f,  0.4f, -0.4f),    glm::vec3( 1.0f,  0.0f,  0.0f),     glm::vec2(1.0f,  1.0f) },
   { glm::vec3( 0.4f, -0.4f, -0.4f),    glm::vec3( 1.0f,  0.0f,  0.0f),     glm::vec2(0.0f,  1.0f) },
   { glm::vec3( 0.4f, -0.4f,  0.4f),    glm::vec3( 1.0f,  0.0f,  0.0f),     glm::vec2(0.0f,  0.0f) },

   { glm::vec3(-0.4f, -0.4f, -0.4f),    glm::vec3( 0.0f, -1.0f,  0.0f),     glm::vec2(0.0f,  1.0f) },
   { glm::vec3( 0.4f, -0.4f, -0.4f),    glm::vec3( 0.0f, -1.0f,  0.0f),     glm::vec2(1.0f,  1.0f) },
   { glm::vec3( 0.4f, -0.4f,  0.4f),    glm::vec3( 0.0f, -1.0f,  0.0f),     glm::vec2(1.0f,  0.0f) },
   { glm::vec3(-0.4f, -0.4f,  0.4f),    glm::vec3( 0.0f, -1.0f,  0.0f),     glm::vec2(0.0f,  0.0f) },

   { glm::vec3(-0.4f,  0.4f, -0.4f),    glm::vec3( 0.0f,  1.0f,  0.0f),     glm::vec2(0.0f,  1.0f) },
   { glm::vec3( 0.4f,  0.4f, -0.4f),    glm::vec3( 0.0f,  1.0f,  0.0f),     glm::vec2(1.0f,  1.0f) },
   { glm::vec3( 0.4f,  0.4f,  0.4f),    glm::vec3( 0.0f,  1.0f,  0.0f),     glm::vec2(1.0f,  0.0f) },
   { glm::vec3(-0.4f,  0.4f,  0.4f),    glm::vec3( 0.0f,  1.0f,  0.0f),     glm::vec2(0.0f,  0.0f) },
};

std::vector<GLuint> space_cube_indexes =
{
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    8, 9, 10,
    10, 11, 8,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20,
};

std::vector<Vertex> space_lamp_vertices =
{
    { glm::vec3(-0.1f, -0.1f,  0.1f) },
    { glm::vec3(-0.1f, -0.1f, -0.1f) },
    { glm::vec3( 0.1f, -0.1f, -0.1f) },
    { glm::vec3( 0.1f, -0.1f,  0.1f) },
    { glm::vec3(-0.1f,  0.1f,  0.1f) },
    { glm::vec3(-0.1f,  0.1f, -0.1f) },
    { glm::vec3( 0.1f,  0.1f, -0.1f) },
    { glm::vec3( 0.1f,  0.1f,  0.1f) },
};

std::vector<GLuint> space_lamp_indexes =
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
