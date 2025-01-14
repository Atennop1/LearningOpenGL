#ifndef LEARNINGOPENGL_INCLUDE_SYSTEM_MODEL_HPP_
#define LEARNINGOPENGL_INCLUDE_SYSTEM_MODEL_HPP_

#include "shader.hpp"
#include "camera.hpp"
#include "vertex.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "json/json.hpp"
#include <glm/gtc/quaternion.hpp>
#include <vector>

class Model
{
public:
    explicit Model(const char *filename);
    void Draw(const Shader &shader, Camera &camera);

private:
    std::vector<unsigned char> GetDataBytes();
    std::vector<float> GetFloats(nlohmann::json accessor);
    std::vector<GLuint> GetIndexes(nlohmann::json accessor);
    std::vector<Texture> GetTextures();

    void LoadMesh(unsigned int mesh_index);
    void TraverseNode(unsigned int next_node, glm::mat4 matrix = glm::mat4(1.0f));

    std::vector<glm::vec2> GroupFloatsInVec2(std::vector<float> floats);
    std::vector<glm::vec3> GroupFloatsInVec3(std::vector<float> floats);
    std::vector<glm::vec4> GroupFloatsInVec4(std::vector<float> floats);
    std::vector<Vertex> AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texture_coords);

    std::string filename_;
    nlohmann::json JSON_;
    std::vector<unsigned char> data_bytes_;
    std::vector<Texture> loaded_textures_;
    std::vector<std::string> loaded_textures_names_;

    std::vector<Mesh> meshes_;
    std::vector<glm::vec3> translations_meshes_;
    std::vector<glm::quat> rotations_meshes_;
    std::vector<glm::vec3> scales_meshes_;
    std::vector<glm::mat4> matrices_meshes_;
};

#endif
