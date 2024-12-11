#ifndef LEARNINGOPENGL_INCLUDE_SHADER_HPP_
#define LEARNINGOPENGL_INCLUDE_SHADER_HPP_

#include "glad/glad.h"

class Shader
{
public:
    Shader(const char *vertex_source_file, const char *fragment_source_file);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Activate() const;
    void Delete() const;

private:
    GLuint id_;
};

#endif
