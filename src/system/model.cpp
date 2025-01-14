#include "system/model.hpp"
#include "system/utils.hpp"
#include "glm/gtc/type_ptr.hpp"

Model::Model(const char *filename)
{
    filename_ = filename;
    JSON_ = nlohmann::json::parse(GetFileContents(filename));
    data_bytes_ = GetDataBytes();
    TraverseNode(0);
}

void Model::Draw(const Shader &shader, Camera &camera)
{
    for (unsigned int i = 0; i < meshes_.size(); ++i)
        meshes_[i].Draw(shader, camera, matrices_meshes_[i]);
}

std::vector<unsigned char> Model::GetDataBytes()
{
    std::string uri = JSON_["buffers"][0]["uri"];
    std::string subdirectory = filename_.substr(0, filename_.find_last_of('/') + 1);
    std::string bytes_text = GetFileContents((subdirectory + uri).c_str());
    return { bytes_text.begin(), bytes_text.end() };
}

std::vector<float> Model::GetFloats(nlohmann::json accessor)
{
    unsigned int count = accessor["count"];
    unsigned int accessor_byte_offset = accessor.value("byteOffset", 0);
    unsigned int buffer_view_index = accessor.value("bufferView", 1);
    std::string type = accessor["type"];

    if (type != "SCALAR" && type != "VEC2" && type != "VEC3" && type != "VEC4")
        throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3 or VEC4)");

    nlohmann::json buffer_view = JSON_["bufferViews"][buffer_view_index];
    unsigned int byte_offset = buffer_view["byteOffset"];
    unsigned int number_per_vertex = (type == "SCALAR" ? 1 : (type == "VEC2" ? 2 : (type == "VEC3" ? 3 : 4)));

    unsigned int start_of_data = byte_offset + accessor_byte_offset;
    unsigned int length_of_data = 4 * count * number_per_vertex;

    std::vector<float> floats;
    for (unsigned int i = start_of_data; i < start_of_data + length_of_data; i)
    {
        float value = 0.0f;
        unsigned char bytes[] = { data_bytes_[i++], data_bytes_[i++], data_bytes_[i++], data_bytes_[i++] };

        std::memcpy(&value, bytes, sizeof (float));
        floats.push_back(value);
    }

    return floats;
}

std::vector<GLuint> Model::GetIndexes(nlohmann::json accessor)
{
    unsigned int count = accessor["count"];
    unsigned int accessor_byte_offset = accessor.value("byteOffset", 0);
    unsigned int buffer_view_index = accessor.value("bufferView", 1);
    unsigned int component_type = accessor["componentType"];

    if (component_type != 5125 && component_type != 5123 && component_type != 5122)
        throw std::invalid_argument("Type is invalid (not unsigned int, unsigned short or short)");

    nlohmann::json buffer_view = JSON_["bufferViews"][buffer_view_index];
    unsigned int byte_offset = buffer_view["byteOffset"];
    unsigned int start_of_data = byte_offset + accessor_byte_offset;

    std::vector<GLuint> indexes;
    for (unsigned int i = start_of_data; i < start_of_data + (component_type == 5125 ? 4 : 2) * count; i += (component_type == 5125 ? 4 : 2))
    {
        unsigned int ui_value = 0;
        unsigned short us_value = 0;
        short s_value = 0;

        unsigned char i_bytes[] = { data_bytes_[i], data_bytes_[i + 1], data_bytes_[i + 2], data_bytes_[i + 3]};
        unsigned char s_bytes[] = { data_bytes_[i], data_bytes_[i + 1] };

        std::memcpy(&ui_value, i_bytes, sizeof(unsigned int));
        std::memcpy(&us_value, s_bytes, sizeof(unsigned short));
        std::memcpy(&s_value, s_bytes, sizeof(short));

        indexes.push_back((component_type == 5125 ? ui_value : (component_type == 5123 ? us_value : s_value)));
    }

    return indexes;
}

std::vector<Texture> Model::GetTextures()
{
    std::vector<Texture> textures;
    std::string subdirectory = filename_.substr(0, filename_.find_last_of('/') + 1);

    for (unsigned int i = 0; i < JSON_["images"].size(); ++i)
    {
        std::string texture_path = JSON_["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; j < loaded_textures_.size(); ++j)
        {
            if (loaded_textures_names_[j] != texture_path)
                continue;

            textures.push_back(loaded_textures_[j]);
            skip = true;
            break;
        }

        if (skip)
            continue;

        Texture texture = Texture((subdirectory + texture_path).c_str(), (texture_path.find("baseColor") != std::string::npos ? "diffuse" : "specular"), loaded_textures_.size());
        textures.push_back(texture);
        loaded_textures_.push_back(texture);
        loaded_textures_names_.push_back(texture_path);
    }

    return textures;
}

void Model::LoadMesh(unsigned int mesh_index)
{
    unsigned int position_accessor_index = JSON_["meshes"][mesh_index]["primitives"][0]["attribute"]["POSITION"];
    unsigned int normal_accessor_index = JSON_["meshes"][mesh_index]["primitives"][0]["attribute"]["NORMAL"];
    unsigned int texture_UV_accessor_index = JSON_["meshes"][mesh_index]["primitives"][0]["attribute"]["TEXCOORD_0"];
    unsigned int indexes_accessor_index = JSON_["meshes"][mesh_index]["primitives"][0]["attribute"]["indices"];

    std::vector<float> position_vectors = GetFloats(JSON_["accessors"][position_accessor_index]);
    std::vector<float> normal_vectors = GetFloats(JSON_["accessors"][normal_accessor_index]);
    std::vector<float> texture_UV_vectors = GetFloats(JSON_["accessors"][texture_UV_accessor_index]);
    std::vector<glm::vec3> positions = GroupFloatsInVec3(position_vectors);
    std::vector<glm::vec3> normals = GroupFloatsInVec3(normal_vectors);
    std::vector<glm::vec2> textures_UV = GroupFloatsInVec2(texture_UV_vectors);

    std::vector<Vertex> vertices = AssembleVertices(positions, normals, textures_UV);
    std::vector<GLuint> indexes = GetIndexes(JSON_["accessors"][indexes_accessor_index]);
    std::vector<Texture> textures = GetTextures();

    meshes_.emplace_back(vertices, indexes, textures);
}

void Model::TraverseNode(unsigned int next_node, glm::mat4 matrix)
{
    nlohmann::json node = JSON_["nodes"][next_node];

    glm::vec3 translation = node.find("translation") == node.end() ? glm::vec3(0.0f, 0.0f, 0.0f) : glm::vec3(node["translation"][0], node["translation"][1], node["translation"][2]);
    glm::quat rotation = node.find("rotation") == node.end() ? glm::quat(1.0f, 0.0f, 0.0f, 0.0f) : glm::quat(node["rotation"][3], node["rotation"][0], node["rotation"][1], node["rotation"][2]);
    glm::vec3 scale = node.find("scale") == node.end() ? glm::vec3(0.0f, 0.0f, 0.0f) : glm::vec3(node["scale"][0], node["scale"][1], node["scale"][2]);

    glm::mat4 matrix_node = glm::mat4(1.0f);
    if (node.find("matrix") != node.end())
    {
        float matrix_values[16];

        for (unsigned int i = 0; i < node["matrix"].size(); ++i)
            matrix_values[i] = node["matrix"][i];

        matrix_node = glm::make_mat4(matrix_values);
    }

    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 rotation_matrix = glm::mat4_cast(rotation);
    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 matrix_next_node = matrix * matrix_node * translation_matrix * rotation_matrix * scale_matrix;

    if (node.find("mesh") != node.end())
    {
        translations_meshes_.push_back(translation);
        rotations_meshes_.push_back(rotation);
        scales_meshes_.push_back(scale);
        matrices_meshes_.push_back(matrix_next_node);
        LoadMesh(node["mesh"]);
    }

    if (node.find("children") != node.end())
        for (const auto &i : node["children"])
            TraverseNode(i, matrix_next_node);
}

std::vector<glm::vec2> Model::GroupFloatsInVec2(std::vector<float> floats)
{
    std::vector<glm::vec2> vectors = {};

    for (int i = 0; i < floats.size(); i)
        vectors.emplace_back(floats[i++], floats[i++]);

    return vectors;
}

std::vector<glm::vec3> Model::GroupFloatsInVec3(std::vector<float> floats)
{
    std::vector<glm::vec3> vectors = {};

    for (int i = 0; i < floats.size(); i)
        vectors.emplace_back(floats[i++], floats[i++], floats[i++]);

    return vectors;
}

std::vector<glm::vec4> Model::GroupFloatsInVec4(std::vector<float> floats)
{
    std::vector<glm::vec4> vectors = {};

    for (int i = 0; i < floats.size(); i)
        vectors.emplace_back(floats[i++], floats[i++], floats[i++], floats[i++]);

    return vectors;
}

std::vector<Vertex> Model::AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texture_coords)
{
    std::vector<Vertex> vertices = {};

    for (int i = 0; i < positions.size(); i)
        vertices.push_back(Vertex { positions[i], normals[i], texture_coords[i] });

    return vertices;
}
