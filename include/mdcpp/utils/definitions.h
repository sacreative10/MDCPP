//
// Created by sohaibalam on 8/5/25.
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <glm/glm.hpp>

namespace mdcpp {
    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        Vertex(glm::vec3 position, glm::vec2 uv) : position(position), uv(uv) {}
        Vertex(glm::vec3 pos) : position(pos) {}
    };
    struct Triangle {
        Vertex a;
        Vertex b;
        Vertex c;
        Triangle(Vertex a, Vertex b, Vertex c) : a(a), b(b), c(c) {}
    };



};

#endif //DEFINITIONS_H
