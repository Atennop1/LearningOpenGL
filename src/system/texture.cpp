#include "system/texture.hpp"
#include "stb/stb_image.h"
#include <stdexcept>

Texture::Texture(const char *path, const char *texture_type, GLuint slot)
{
    type_ = texture_type;
    int texture_width, texture_height, color_channels_number = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(path, &texture_width, &texture_height, &color_channels_number, 0);

    if (color_channels_number != 1 && color_channels_number != 3 && color_channels_number != 4)
        throw std::invalid_argument("Automatic Texture type recognition failed");

    unit_ = slot;
    glGenTextures(1, &id_);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, (color_channels_number == 4 ? GL_RGBA : (color_channels_number == 3 ? GL_RGB : GL_RED)), GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
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
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() const
{
    glDeleteTextures(1, &id_);
}
