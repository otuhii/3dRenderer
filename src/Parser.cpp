#include "include/Parser.hpp"

#include <iostream>
#include <fstream>

int Parser::ParseAndLinkShader(
        const std::string& filename,
        unsigned int shaderProgram,
        GLenum type
    )
{
    // if (type != GL_VERTEX_SHADER || 
    //     type != GL_FRAGMENT_SHADER)
    // {
    //     std::cout << "WRONG TYPE FOR SHADER PARSING!" << std::endl;
    //     return -1;
    // }
    
    unsigned int 
        shader{};

    shader = glCreateShader(type);

    
    std::string source{
        ParseShader(filename)
    };

    if (source.size() == 0)
    {
        return -1;
    }

    const char* pSource{
        source.c_str()
    };

    glShaderSource(
            shader,
            1,
            &pSource,
            NULL
            );
    glCompileShader(shader);


    int success{};
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n" << "FILENAME: " << filename << std::endl;
        return -1;
    }

    glAttachShader(shaderProgram, shader);
    glDeleteShader(shader);


    return 0;
}


std::string Parser::ParseShader(const std::string& filename)
{
    std::ifstream readFrom(filename);

    if (!readFrom)
    {
        std::cout << "Failed to open file\n" << std::endl;
        return {};
    }

    //i dont really understand iterators but whaeva
    return std::string(
        (std::istreambuf_iterator<char>(readFrom)), 
        std::istreambuf_iterator<char>()
    );
    

}

