//
// Created by sohaibalam on 8/6/25.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include <mdcpp/drawables/drawables.hpp>

namespace mdcpp {

    class Circle : public Drawable {
    public:
        Circle(float radius, glm::vec2 pos, float thickness = 2.f, glm::vec3 colour = glm::vec3(1.f), bool fill = false);

        void draw() override;
    private:
        void setup() override;
        float m_radius;
        glm::vec2 m_pos;
        std::vector<glm::vec3> m_vertices = {
            glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, -1, 0),
            glm::vec3(-1, 1, 0), glm::vec3(1, -1, 0), glm::vec3(-1, -1, 0)
        };
        std::vector<glm::vec2> m_uvs = {
            glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0),
            glm::vec2(0, 1), glm::vec2(1, 0), glm::vec2(0, 0)
        };



    };

};


#endif //CIRCLE_H
