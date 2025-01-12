#ifndef LEARNINGOPENGL_INCLUDE_UTILS_HPP_
#define LEARNINGOPENGL_INCLUDE_UTILS_HPP_

#include <string>
#include <fstream>
#include <iostream>

std::string GetFileContents(const char* filename)
{
    auto file = std::ifstream(filename, std::ios::binary);

    if (!file)
        throw std::exception();

    std::string contents;
    file.seekg(0, std::ios::end);
    contents.resize(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(&contents[0], std::streamsize(contents.size()));
    file.close();

    return(contents);
}

void CompileShaderErrors(unsigned int shader, const char *type)
{
    GLint has_compiled;
    char info_log[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
        if (has_compiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, info_log);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << info_log << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &has_compiled);
        if (has_compiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, info_log);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << info_log << std::endl;
        }
    }
}

#endif
