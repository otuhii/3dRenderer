//
// Created by otuhii on 10/23/26.
//

#ifndef RENDERER_UTILITY_H
#define RENDERER_UTILITY_H

#include <cinttypes>

struct Vertex {
    float x{};
    float y{};
    float z{};
};

struct Face {
    uint16_t v1{};
    uint16_t v2{};
    uint16_t v3{};
};


#endif //RENDERER_UTILITY_H
