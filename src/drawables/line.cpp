#include "mdcpp/drawables/drawables.hpp"
#include <mdcpp/drawables/line.hpp>
#include <mdcpp/utils/shaders.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace mdcpp {

Line::Line(glm::vec2 start, glm::vec2 end, float thickness, glm::vec3 colour): m_start(start), m_end(end), Drawable(thickness, colour, false){
	setup();
}


void Line::updateBuffer()
{
	glm::vec2 dir = glm::normalize(m_end - m_start);
	glm::vec2 perp = glm::vec2(-dir.y, dir.x) * m_thickness * 0.5f;

	glm::vec2 v0 = m_start + perp;
	glm::vec2 v1 = m_start - perp;
	glm::vec2 v2 = m_end + perp;
	glm::vec2 v3 = m_end - perp;

	glm::vec3 verts[4] = {
		glm::vec3(v0.x, v0.y, 0.0f),
		glm::vec3(v1.x, v1.y, 0.0f),
		glm::vec3(v2.x, v2.y, 0.0f),
		glm::vec3(v3.x, v3.y, 0.0f)
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * 4, verts);
}

void Line::updatePoints(glm::vec2 start, glm::vec2 end)
{
	m_start = start;
	m_end = end;
	updateBuffer();
}

void Line::setup()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 4, nullptr, GL_DYNAMIC_DRAW);

	updateBuffer();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
	

	glBindVertexArray(0);

	m_shaderProgram = loadShader("shaders/line_vert.glsl", "shaders/line_frag.glsl");
}

void Line::draw()
{
	glUseProgram(0);
	glUseProgram(m_shaderProgram);
	
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uMVP"), 1, GL_FALSE, glm::value_ptr(m_mvpMatrix));
	glUniform3fv(glGetUniformLocation(m_shaderProgram, "uColor"), 1, glm::value_ptr(m_colour));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUseProgram(0);
	glBindVertexArray(0);
}
};
