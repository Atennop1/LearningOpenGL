#ifndef LEARNINGOPENGL_INCLUDE_SYSTEM_VERTEX_HPP_
#define LEARNINGOPENGL_INCLUDE_SYSTEM_VERTEX_HPP_

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_UV;
};

#endif
