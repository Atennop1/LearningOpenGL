#ifndef LEARNINGOPENGL_INCLUDE_SYSTEM_TEXTURE_HPP_
#define LEARNINGOPENGL_INCLUDE_SYSTEM_TEXTURE_HPP_

#include "glad/glad.h"
#include "shader.hpp"

class Texture
{
public:
    Texture(const char *path, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type);
    [[nodiscard]] GLuint GetID() const { return id_; }

    void Activate(const Shader &shader, const char *uniform_name, GLint texture_slot) const;
    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint id_{};
    GLuint unit_{};
    GLenum type_{};
};

#endif
