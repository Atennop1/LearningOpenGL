#ifndef LEARNINGOPENGL_INCLUDE_SYSTEM_MESH_HPP_
#define LEARNINGOPENGL_INCLUDE_SYSTEM_MESH_HPP_

#include "vertex.hpp"
#include "vao.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include <glad/glad.h>
#include <vector>
#include <string>

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indexes, const std::vector<std::pair<std::string, Texture>> &textures);
    void Draw(const Shader &shader, Camera &camera);

private:
    std::vector<Vertex> vertices_;
    std::vector<GLuint> indexes_;
    std::vector<std::pair<std::string, Texture>> textures_;

    VAO VAO_{};
};

#endif
