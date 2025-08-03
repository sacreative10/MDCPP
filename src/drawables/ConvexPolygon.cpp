
#include "mdcpp/drawables/drawables.hpp"
#include <mdcpp/drawables/polygon.hpp>
#include <mdcpp/utils/shaders.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>


namespace mdcpp {
ConvexPolygon::ConvexPolygon(std::vector<glm::vec2> vertices, float thickness, glm::vec3 colour, bool fill)
: m_vertices(vertices), Drawable(thickness, colour, fill)
{
	setup();
}

void ConvexPolygon::setup()
{
	m_indexCount = m_vertices.size();
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_indexCount, nullptr, GL_DYNAMIC_DRAW);

	updateBuffer();

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	m_shaderProgram = loadShader("shaders/line_vert.glsl", "shaders/line_frag.glsl");
}

void ConvexPolygon::updateBuffer()
{
	size_t newCount = m_vertices.size();
	if(newCount != m_indexCount)
	{
		m_indexCount = newCount;
		glDeleteBuffers(1, &m_VBO);
		glGenBuffers(1, &m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_indexCount, nullptr, GL_DYNAMIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * m_indexCount, m_vertices.data());
}

void ConvexPolygon::draw()
{
	glUseProgram(m_shaderProgram);

	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uMVP"), 1, GL_FALSE, glm::value_ptr(m_mvpMatrix));
	glUniform3fv(glGetUniformLocation(m_shaderProgram, "uColor"), 1, glm::value_ptr(m_colour));

	glLineWidth(m_thickness);
	glBindVertexArray(m_VAO);
	if (m_fill)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, m_indexCount);
	}
	glDrawArrays(GL_LINE_LOOP, 0, m_indexCount);

	glUseProgram(0);
	glBindVertexArray(0);
}


Quad::Quad(glm::vec2 pos, float width, float height, float thickness, glm::vec3 colour, bool fill)
: m_pos(pos), m_width(width), m_height(height), Drawable(thickness, colour, fill)
{
	setup();
}

void Quad::updateBuffer()
{
	glm::vec2 v0 = glm::vec2(m_pos.x - m_width * 0.5f, m_pos.y - m_height * 0.5f);
	glm::vec2 v1 = glm::vec2(m_pos.x + m_width * 0.5f, m_pos.y - m_height * 0.5f);
	glm::vec2 v2 = glm::vec2(m_pos.x + m_width * 0.5f, m_pos.y + m_height * 0.5f);
	glm::vec2 v3 = glm::vec2(m_pos.x - m_width * 0.5f, m_pos.y + m_height * 0.5f);

	std::vector<glm::vec2> vertices = {v0, v1, v2, v3};
	m_polygon = new ConvexPolygon(vertices, m_thickness, m_colour, m_fill);
}

void Quad::setup()
{
	updateBuffer();
}

void Quad::draw()
{
	m_polygon->draw();
}
void Quad::setPos(glm::vec2 pos)
{
	m_pos = pos;
	updateBuffer();
}

};





