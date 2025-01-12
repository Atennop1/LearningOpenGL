#include "system/texture.hpp"
#include "stb/stb_image.h"

Texture::Texture(const char *path, GLenum texture_type, GLuint slot, GLenum format, GLenum pixel_type)
{
    type_ = texture_type;
    int texture_width, texture_height, color_channels_number = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(path, &texture_width, &texture_height, &color_channels_number, 0);

    unit_ = slot;
    glGenTextures(1, &id_);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(type_, id_);

    glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type_, 0, GL_RGBA, texture_width, texture_height, 0, format, pixel_type, bytes);
    glGenerateMipmap(type_);

    stbi_image_free(bytes);
    glBindTexture(type_, 0);
}

void Texture::Activate(const Shader &shader, const char *uniform_name, GLint slot) const
{
    GLint uniform_ID = glGetUniformLocation(shader.GetID(), uniform_name);
    shader.Activate();
    glUniform1i(uniform_ID, slot);
}

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + unit_);
    glBindTexture(type_, id_);
}

void Texture::Unbind() const
{
    glBindTexture(type_, 0);
}

void Texture::Delete() const
{
    glDeleteTextures(1, &id_);
}
