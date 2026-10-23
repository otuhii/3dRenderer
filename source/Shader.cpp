//
// Created by otuhii on 10/23/26.
//

#include <Shader.h>

Shader::Shader(std::string const &vertex_filepath, std::string const &fragment_filepath)
{
    shader_program_ = glCreateProgram();

    uint32_t vertex_shader(Parser::ParseShader(vertex_filepath));
    uint32_t fragment_shader(Parser::ParseShader(fragment_filepath));
    glAttachShader(shader_program_, vertex_shader);
    glAttachShader(shader_program_, fragment_shader);

    glLinkProgram(shader_program_);

    int success{};
    char infoLog[512]{};
    glGetProgramiv(shader_program_,GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program_, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n\n" << infoLog << std::endl;
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        throw std::runtime_error("Failed to create shader");
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    glDeleteProgram(shader_program_);
}

void Shader::Bind() const
{
    glUseProgram(shader_program_);
}
