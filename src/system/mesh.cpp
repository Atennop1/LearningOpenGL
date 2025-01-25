#include "system/mesh.hpp"
#include "system/ebo.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <map>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indexes, const std::vector<std::pair<std::string, Texture>> &textures)
{
    vertices_ = vertices;
    indexes_ = indexes;
    textures_ = textures;

    InitBuffers();
}

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indexes, const std::vector<Texture> &textures)
{
    std::map<const char*, int> counts;
    std::vector<std::pair<std::string, Texture>> pairs;

    for (auto texture : textures)
    {
        if (counts.find(texture.GetType()) == counts.end())
            counts.insert({ texture.GetType(), 0 });

        std::string number = std::to_string(counts[texture.GetType()]++);
        pairs.emplace_back(texture.GetType() + number, texture);
    }

    vertices_ = vertices;
    indexes_ = indexes;
    textures_ = pairs;
    InitBuffers();
}

void Mesh::InitBuffers()
{
    VAO_ = VAO();
    VBO_ = VBO(vertices_);
    EBO_ = EBO(indexes_);

    VAO_.LinkAttributes(VBO_, 0, 3, GL_FLOAT, sizeof (Vertex), (void*) nullptr);
    VAO_.LinkAttributes(VBO_, 1, 3, GL_FLOAT, sizeof (Vertex), (void*)(3 * sizeof (float)));
    VAO_.LinkAttributes(VBO_, 2, 2, GL_FLOAT, sizeof (Vertex), (void*)(6 * sizeof (float)));

    VAO_.Unbind();
    VBO_.Unbind();
    EBO_.Unbind();
}

Mesh::~Mesh()
{
    VAO_.Delete();
    VBO_.Delete();
    EBO_.Delete();
}

void Mesh::Draw(const Shader &shader, Camera &camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
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

    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 rotation_matrix = glm::mat4_cast(rotation);
    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scale);

    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "translation"), 1, GL_FALSE, glm::value_ptr(translation_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "rotation"), 1, GL_FALSE, glm::value_ptr(rotation_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "scale"), 1, GL_FALSE, glm::value_ptr(scale_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));
    glDrawElements(GL_TRIANGLES, (GLsizei)indexes_.size(), GL_UNSIGNED_INT, nullptr);
}
