#include "system/shader.hpp"
#include "system/utils.hpp"

Shader::Shader(const char *vertex_source_file, const char *fragment_source_file)
{
    auto vertex_code = GetFileContents(vertex_source_file);
    auto fragment_code = GetFileContents(fragment_source_file);

    auto vertex_source = vertex_code.c_str();
    auto fragment_source = fragment_code.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
    glCompileShader(fragment_shader);

    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader);
    glAttachShader(id_, fragment_shader);
    glLinkProgram(id_);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::Activate() const
{
    glUseProgram(id_);
}

void Shader::Delete() const
{
    glDeleteProgram(id_);
}
