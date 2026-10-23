//
// Created by otuhii on 10/23/26.
//

#ifndef RENDERER_MODEL_H
#define RENDERER_MODEL_H

#include <utility.h>

#include <string>
#include <vector>

class Model {
public:
    explicit Model() = default;
    explicit Model(std::vector<Vertex> const& vertices, std::vector<Face> const& faceIndices)
        :vertices_(vertices), faceIndices_(faceIndices) {}
    explicit Model(std::vector<Vertex>&& vertices, std::vector<Face>&& faceIndices)
        :vertices_(std::move(vertices)), faceIndices_(std::move(faceIndices)){}


    inline size_t GetVertexCount() const
    { return vertices_.size(); }
    inline size_t GetFaceCount() const
    {return faceIndices_.size();}

    inline std::vector<Vertex> const& GetVertices() const
    { return vertices_; }
    inline std::vector<Face> const& GetFaces() const
    {return faceIndices_; }

private:
    std::vector<Vertex>     vertices_;
    std::vector<Face>   faceIndices_;

    std::vector<std::string> file_comments_;
};

#endif //RENDERER_MODEL_H
