#ifndef LEARNINGOPENGL_INCLUDE_UTILS_HPP_
#define LEARNINGOPENGL_INCLUDE_UTILS_HPP_

#include <string>
#include <fstream>

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

#endif
