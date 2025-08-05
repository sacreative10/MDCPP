
#include "mdcpp/drawables/drawables.hpp"
#include "mdcpp/texture.hpp"
#include <mdcpp/drawables/vertex.hpp>
#include <mdcpp/utils/shaders.hpp>
#include <glm/ext.hpp>
#include <spdlog/spdlog.h>


namespace mdcpp {

Vertices::Vertices(std::vector<Vertex> vertices, RenderType renderType) : m_vertices(vertices), m_renderType(renderType)
	,Drawable(){
	setup();
}

Vertices::Vertices(std::vector<glm::vec3> vertices, RenderType renderType) :m_points(vertices), m_renderType(renderType), Drawable() {

	for (const auto& v: m_points)
	{
		m_vertices.emplace_back(v, glm::vec2(0.f, 0.f));
	}


	setup();
}

Vertices::Vertices(std::vector<Triangle> triangles, RenderType renderType) : m_renderType(renderType), Drawable() {
	for (const auto& t: triangles) {
		m_vertices.emplace_back(t.a);
		m_vertices.emplace_back(t.b);
		m_vertices.emplace_back(t.c);
	}

	setup();
}


void Vertices::updateBuffer() 
{

	size_t newCount = m_vertices.size();
	if(newCount != m_indexCount)
	{
		m_indexCount = newCount;
		glDeleteBuffers(1, &m_VBO);
		glGenBuffers(1, &m_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_indexCount, nullptr, GL_DYNAMIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_indexCount, m_vertices.data());

}

void Vertices::setup()
{
	m_indexCount = m_vertices.size();

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_indexCount, nullptr, GL_DYNAMIC_DRAW);

	updateBuffer();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	m_shaderProgram = loadShader("shaders/vertex_vert.glsl", "shaders/vertex_frag.glsl");
}

void Vertices::draw() 
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_shaderProgram);

	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "uMVP"), 1, GL_FALSE, glm::value_ptr(m_mvpMatrix));

	glBindVertexArray(m_VAO);
	if (m_renderType == RenderType::NO_FILL)
	{
		glUniform1i(glGetUniformLocation(m_shaderProgram, "uWireframe"), 1);
		m_colour = glm::vec3(1.f, 1.f, 1.f);
		glUniform3fv(glGetUniformLocation(m_shaderProgram, "uColor"), 1, glm::value_ptr(m_colour));

		glLineWidth(m_thickness);
		glDrawArrays(GL_LINE_LOOP, 0, m_indexCount);
	} else if(m_renderType == RenderType::TEXTURE && m_texture != nullptr)
	{
		glUniform1i(glGetUniformLocation(m_shaderProgram, "uWireframe"), 0);
		glUniform1i(glGetUniformLocation(m_shaderProgram, "uTexture"), 0);
		m_texture->bind(0);
		glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
	}

	glUseProgram(0);
	glBindVertexArray(0);
	m_texture->unbind();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
}


};
