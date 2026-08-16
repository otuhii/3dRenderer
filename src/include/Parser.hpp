#include <string>
#include <glad/gl.h>


class Parser{
public:
    enum class ShaderType{
        vertex,
        fragment
    };

    Parser() = delete;
    
    static int ParseAndLinkShader(
            const std::string& filename, 
            unsigned int shaderProgram, 
            GLenum type
    );

private:

    static std::string ParseShader(const std::string& filename);


};
