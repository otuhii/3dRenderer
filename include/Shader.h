//
// Created by otuhii on 10/23/26.
//

#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include <string>
#include <Parser.h>

class Shader {
public:
    explicit Shader(
        std::string const& vertex_filepath,
        std::string const& fragment_filepath
    );

    Shader(Shader const&) = delete;
    Shader& operator=(Shader const&) = delete;
    Shader(Shader&&) = delete;
    Shader& operator=(Shader&&) = delete;
    ~Shader();

    void Bind() const;

private:
    uint32_t shader_program_{};
};


#endif //RENDERER_SHADER_H
