//
// Created by otuhii on 10/22/26.
//

#include <Parser.h>

Model Parser::ParseModel(const std::string &filepath)
{
    std::string
        file_extension{fs::path(filepath).extension()};

    if (file_extension == ".obj")
    {
        return ParseObj(filepath);
    }

    if (file_extension == ".bobj")
    {
        return ParsebObj(filepath);
    }

    std::cerr << "this file is not supported. FILE - " << filepath << std::endl;
    return Model{};
}

uint32_t Parser::ParseShader(const std::string &filepath)
{
    std::string
        file_extension{fs::path(filepath).extension()};

    if (file_extension == ".frag")
    {
        return ParseFragmentShader(filepath);
    }

    if (file_extension == ".vert")
    {
        return ParseVertexShader(filepath);
    }

    std::cerr << "wrong shader type!. FILE - " << filepath << "\n";
    return 0;
}

bool Parser::SaveModel(const std::string &filepath, Model const &model)
{
    std::string
        file_extension{fs::path(filepath).extension()};

    if (file_extension == ".obj")
    {
        return SaveObj(filepath, model);
    }

    if (file_extension == ".bobj")
    {
        return SavebObj(filepath, model);
    }

    std::cerr << "this file is not supported. FILE - " << filepath << "\n";
    return false;
}

void Parser::split(const std::string &readline, std::vector<std::string> &splitted_line, char separator)
{
    size_t
        next_position {readline.find( separator )};
    size_t
        start_position{};

    splitted_line.clear();

    while( next_position != std::string::npos ) {
        splitted_line.push_back( readline.substr( start_position, next_position - start_position ) );
        start_position = next_position + 1;

        next_position = readline.find( separator, start_position );
    }

    splitted_line.push_back( readline.substr( start_position, std::min( next_position, readline.size() ) - start_position + 1 ) );
}

Model Parser::ParseObj(std::string const& filepath)
{
    if (std::ifstream model_file{filepath}; model_file)
    {
        std::string current_read_line{};

        std::vector<std::string> splitted_string{};

        //std::vector<std::string> comments{};

        std::vector<Face>       faces{};
        std::vector<Vertex>   vertices{};

        while (getline(model_file, current_read_line))
        {
            split(current_read_line, splitted_string, ' ');

            //fuck comments
            // if (splitted_string[0] == "#")
            // {
            //     comments.push_back(current_read_line);
            // }
            if (splitted_string[0] == "v")
            {
                vertices.push_back(Vertex{
                    std::stof(splitted_string[1]),
                    std::stof(splitted_string[2]),
                    std::stof(splitted_string[3])
                });
            }
            else if (splitted_string[0] == "f")
            {
                faces.push_back(Face{
                    static_cast<uint16_t>(std::stoi(splitted_string[1])),
                    static_cast<uint16_t>(std::stoi(splitted_string[2])),
                    static_cast<uint16_t>(std::stoi(splitted_string[3]))
                });
            }
        }
        model_file.close();

        return Model{std::move(vertices), std::move(faces)};
    }

    std::cerr << "Error opening model file\nFilepath - " << filepath << "\n";
    return Model{};
}

Model Parser::ParsebObj(std::string const &filepath)
{
    if (std::ifstream model_file{filepath, std::ios::binary}; model_file)
    {
        std::vector<Face>       faces{};
        std::vector<Vertex>     vertices{};

        size_t vertex_count{};
        size_t face_count{};

        model_file.read(
            reinterpret_cast<char*>(&vertex_count),
            sizeof(vertex_count)
        );
        model_file.read(
            reinterpret_cast<char*>(&face_count),
            sizeof(face_count)
        );
        vertices.resize(vertex_count);
        faces.resize(face_count);

        model_file.read(
            reinterpret_cast<char*>(vertices.data()),
            vertices.size() * sizeof(vertices.front())
        );
        model_file.read(
            reinterpret_cast<char*>(faces.data()),
            faces.size() * sizeof(vertices.front())
        );

        model_file.close();

        return Model{std::move(vertices), std::move(faces)};
    }

    std::cerr << "Error opening model file\nFilepath - " << filepath << "\n";
    return Model{};
}

uint32_t Parser::ParseVertexShader(std::string const &filepath)
{
    uint32_t
        vertex_shader_idx{glCreateShader(GL_VERTEX_SHADER)};

    std::string
        shader_source{std::move(ReadShaderSource(filepath))};

    CompileShader(vertex_shader_idx, shader_source);

    return vertex_shader_idx;
}

uint32_t Parser::ParseFragmentShader(std::string const &filepath)
{
    uint32_t
        fragment_shader_idx{glCreateShader(GL_FRAGMENT_SHADER)};

    std::string
        shader_source{std::move(ReadShaderSource(filepath))};

    CompileShader(fragment_shader_idx, shader_source);

    return fragment_shader_idx;
}


std::string Parser::ReadShaderSource(std::string const &filepath)
{
    if (std::ifstream input_file(filepath); input_file)
    {
        std::string
            current_read_line{};
        std::string
            shader_source{};

        while (getline(input_file, current_read_line))
        {
            shader_source += current_read_line + "\n";
        }

        return shader_source;
    }
    std::cerr << "Failed to open file - " << filepath << "\n";
    return {};
}

void Parser::CompileShader(uint32_t shader_handle, std::string const &shader_source)
{
    const char*
        pSource{shader_source.c_str()};

    glShaderSource(
         shader_handle,
         1,
         &pSource,
        NULL
    );
    glCompileShader(shader_handle);

    int success{};
    char infoLog[512];
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_handle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n" << "\n";
    }
}


bool Parser::SaveObj(const std::string &filepath, Model const &model)
{
    if (std::ofstream output_file{filepath}; output_file)
    {
        for (Vertex const& vertex : model.GetVertices())
        {
            output_file << "v " <<
                    vertex.x << " " <<
                    vertex.y << " " <<
                    vertex.z << "\n";
        }

        for (Face const& face : model.GetFaces())
        {
            output_file << "f " <<
                    face.v1 << " " <<
                    face.v2 << " " <<
                    face.v3 << "\n";
        }
        output_file.close();

        return true;
    }

    std::cerr << "Error opening file when saving model to " << filepath << "\n";
    return false;
}

bool Parser::SavebObj(const std::string &filepath, Model const &model)
{
    //first write two values for count of vertices and faces and then parser will know how to read it
    //first we write vertices and then faces
    //[vertexCount]   [faceCount]   [vertices]   [faces]
    if (std::ofstream output_file{filepath, std::ios::binary}; output_file)
    {
        size_t vertex_count{model.GetVertexCount()};
        size_t face_count{model.GetFaceCount()};
        output_file.write(
            reinterpret_cast<const char*>(&vertex_count),
            sizeof(vertex_count)
        );
        output_file.write(
            reinterpret_cast<const char*>(&face_count),
            sizeof(face_count)
        );


        std::vector<Vertex> const& vertices_alias{model.GetVertices()};
        std::vector<Face> const& faces_alias{model.GetFaces()};
        output_file.write(
            reinterpret_cast<const char*>(vertices_alias.data()),
            vertices_alias.size() * sizeof(vertices_alias.front())
        );

        output_file.write(
            reinterpret_cast<const char*>(faces_alias.data()),
            faces_alias.size() * sizeof(faces_alias.front())
        );


        return true;
    }

    std::cerr << "Error opening file when saving model to " << filepath << "\n";
    return false;
}


