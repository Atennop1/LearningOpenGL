#include "system/mesh.hpp"
#include "system/ebo.hpp"
#include <string>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indexes, const std::vector<std::pair<std::string, Texture>> &textures)
{
    vertices_ = vertices;
    indexes_ = indexes;
    textures_ = textures;

    VAO_ = VAO();
    auto vbo = VBO(vertices);
    auto ebo = EBO(indexes);

    VAO_.LinkAttributes(vbo, 0, 3, GL_FLOAT, sizeof (Vertex), (void*) nullptr);
    VAO_.LinkAttributes(vbo, 1, 3, GL_FLOAT, sizeof (Vertex), (void*)(3 * sizeof (float)));
    VAO_.LinkAttributes(vbo, 2, 2, GL_FLOAT, sizeof (Vertex), (void*)(6 * sizeof (float)));

    VAO_.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw(const Shader &shader, Camera &camera)
{
    shader.Activate();
    VAO_.Bind();

    for (int i = 0; i < textures_.size(); ++i)
    {
        textures_[i].second.Activate(shader, textures_[i].first.c_str(), i);
        textures_[i].second.Bind();
    }

    camera.DisplayMatrix(shader, "camera_matrix");
    glUniform3f(glGetUniformLocation(shader.GetID(), "camera_position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
    glDrawElements(GL_TRIANGLES, indexes_.size(), GL_UNSIGNED_INT, nullptr);
}
