#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_PYRAMID_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_PYRAMID_VERTICES_HPP_

#include "system/vertex.hpp"
#include <glad/glad.h>
#include <vector>

std::vector<Vertex> pyramid_vertices =
{
   { glm::vec3(-0.5f, -0.4f,  0.5f),     glm::vec3(0.00f, 0.00f, 0.00f),     glm::vec2(0.0f, 0.0f) },
   { glm::vec3(-0.5f, -0.4f, -0.5f),     glm::vec3(0.00f, 0.00f, 0.00f),     glm::vec2(1.0f, 0.0f) },
   { glm::vec3( 0.5f, -0.4f, -0.5f),     glm::vec3(0.00f, 0.00f, 0.00f),     glm::vec2(0.0f, 0.0f) },
   { glm::vec3( 0.5f, -0.4f,  0.5f),     glm::vec3(0.00f, 0.00f, 0.00f),     glm::vec2(1.0f, 0.0f) },
   { glm::vec3( 0.0f,  0.4f,  0.0f),     glm::vec3(0.00f, 0.00f, 0.00f),     glm::vec2(0.5f, 1.0f) },
};

std::vector<GLuint> pyramid_indexes =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4,
};

#endif
