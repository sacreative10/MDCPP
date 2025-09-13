//
// Created by sohaibalam on 8/6/25.
//

#include <mdcpp/drawables/circle.h>

#include "glm/gtc/type_ptr.hpp"
#include "mdcpp/utils/shaders.hpp"

namespace mdcpp {
    Circle::Circle(float radius, glm::vec2 pos, float thickness, glm::vec3 colour, bool fill) : m_pos(pos), m_radius(radius), Drawable(thickness, colour, fill) {
        setup();
    }

    void Circle::setup() {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size() + sizeof(glm::vec2) * m_uvs.size(), nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(sizeof(glm::vec3) * m_vertices.size()));
        glEnableVertexAttribArray(1);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * m_vertices.size(), m_vertices.data());
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), sizeof(glm::vec2) * m_uvs.size(), m_uvs.data());

        glBindVertexArray(0);

        m_shaderProgram = loadShader("shaders/circle_vert.glsl", "shaders/circle_frag.glsl");
    }

    void Circle::draw() {
        glEnable(GL_POINT_SPRITE_COORD_ORIGIN);
        glUseProgram(m_shaderProgram);

        m_mvpMatrix = glm::translate(glm::mat4(1.f), glm::vec3(m_pos, 0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(m_radius, m_radius, 1.f)) * m_mvpMatrix;

        float relativeThickness = m_thickness / (2 *m_radius);

        glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uMVP"), 1, GL_FALSE, glm::value_ptr(m_mvpMatrix));
        glUniform3fv(glGetUniformLocation(m_shaderProgram, "uColor"), 1, glm::value_ptr(m_colour));
        glUniform1f(glGetUniformLocation(m_shaderProgram, "uThickness"), relativeThickness);
        glUniform1f(glGetUniformLocation(m_shaderProgram, "uFill"), m_fill);

        // pass uv coordinates

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertices.size());

        glUseProgram(0);
        glBindVertexArray(0);



    }

};
