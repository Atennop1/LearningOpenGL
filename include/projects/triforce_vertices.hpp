#ifndef LEARNINGOPENGL_INCLUDE_PROJECTS_TRIFORCE_VERTICES_HPP_
#define LEARNINGOPENGL_INCLUDE_PROJECTS_TRIFORCE_VERTICES_HPP_

#include "system/vertex.hpp"
#include <glad/glad.h>
#include <cmath>
#include <vector>

std::vector<Vertex> triforce_vertices =
{
    { glm::vec3(-0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f),    glm::vec3(0.8f, 0.3f,  0.02f) },
    { glm::vec3( 0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f),    glm::vec3(0.8f, 0.3f,  0.02f) },
    { glm::vec3( 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f),    glm::vec3(1.0f, 0.6f,  0.32f) },
    { glm::vec3(-0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f),    glm::vec3(0.9f, 0.45f, 0.17f) },
    { glm::vec3( 0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f),    glm::vec3(0.9f, 0.45f, 0.17f) },
    { glm::vec3( 0.0f, -0.5f * float(sqrt(3)) / 3,     0.0f),    glm::vec3(0.8f, 0.3f,  0.02f) },
};

std::vector<GLuint> triforce_indexes =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

#endif
