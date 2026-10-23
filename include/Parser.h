//
// Created by otuhii on 10/22/26.
//

#ifndef OBJCONVERTER_PARSER_H
#define OBJCONVERTER_PARSER_H
#include <Model.h>

#include <glad/gl.h>

#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class Parser {
public:
    static Model ParseModel(const std::string& filepath);
    static uint32_t ParseShader(const std::string& filepath);

    static bool SaveModel(const std::string& filepath, Model const& model);
private:
    static void split(const std::string &readline, std::vector<std::string> &splitted_line, char ch);

    ///parsing
    static Model ParseObj(std::string const& filepath);
    static Model ParsebObj(std::string const& filepath);
    //.... so then i can add more type support

    static uint32_t ParseVertexShader(std::string const& filepath);
    static uint32_t ParseFragmentShader(std::string const& filepath);

    static std::string ReadShaderSource(std::string const& filepath);
    static void CompileShader(uint32_t shader_handle,std::string const& shader_source);


    //saving
    static bool SaveObj(const std::string& filepath, Model const& model);
    static bool SavebObj(const std::string& filepath, Model const& model);
};


#endif //OBJCONVERTER_PARSER_H
