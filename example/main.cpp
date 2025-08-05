
#include <mdcpp/window.hpp>
#include <mdcpp/drawables/polygon.hpp>
#include <mdcpp/drawables/vertex.hpp>
#include <mdcpp/drawables/line.hpp>
#include <glm/ext.hpp>

#include "mdcpp/input/input.h"


std::vector<mdcpp::Triangle> subdivideTriangle(std::vector<mdcpp::Triangle>& verts, int depth) {
	if (depth == 0) return verts;

	std::vector<mdcpp::Triangle> newVerts;
	for (auto& t : verts) {
		glm::vec3 p1 = (t.a.position + t.b.position) / 2.f;
		glm::vec3 p2 = (t.b.position + t.c.position) / 2.f;
		glm::vec3 p3 = (t.c.position + t.a.position) / 2.f;

		newVerts.emplace_back(mdcpp::Triangle(t.a.position, p1, p3));
		newVerts.emplace_back(mdcpp::Triangle(p1, t.b.position, p2));
		newVerts.emplace_back(mdcpp::Triangle(p3, p2, t.c.position));
		newVerts.emplace_back(mdcpp::Triangle(p1, p2, p3));
	}

	return subdivideTriangle(newVerts, depth - 1);
}

glm::vec3 normalize(glm::vec3 a, glm::vec3 b, float length) {
	glm::vec3 dV = b - a;
	float len = glm::length(dV);
	dV *= (length) / len;
	return a + dV;
}

void normalizeTri(std::vector<mdcpp::Triangle>& verts, glm::vec3 origin, float length) {
	for (auto& t : verts) {
		t.a.position = normalize(origin, t.a.position, length);
		t.b.position = normalize(origin, t.b.position, length);
		t.c.position = normalize(origin, t.c.position, length);
	}
}


glm::vec2 getUV(glm::vec3& p) {
	const float EPSILON = 0.0001f;
	glm::vec3 p_ = glm::normalize(p);
	float theta = std::acos(-p_.y);
	float phi = glm::pi<float>() + std::atan2(-p_.z, p_.x);

	auto p__ = glm::vec2{phi / (2 * glm::pi<float>()), theta / glm::pi<float>()};

	if (p__.x > 1.f - EPSILON)
		p__.x -= EPSILON;
	else if (phi < EPSILON)
		p__.x += EPSILON;

	return p__;
}

std::vector<mdcpp::Triangle> octahedronPoints = {
	// top
	mdcpp::Triangle{glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1)},
	mdcpp::Triangle{glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1)},
	mdcpp::Triangle{glm::vec3(0, -1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1)},
	mdcpp::Triangle{glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)},
	// bottom
	mdcpp::Triangle{glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)},
	mdcpp::Triangle{glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)},
	mdcpp::Triangle{glm::vec3(0, -1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, -1)},
	mdcpp::Triangle{glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1)},
};
int main()
{
	mdcpp::Window window(800, 600, "mdcpp");
	auto square = new mdcpp::Quad(glm::vec2(-200, 100), 100, 200, 2.f, glm::vec3(0.f, 0.f, 1.f), true);

	struct triangle {
		glm::vec2 v0;
		glm::vec2 v1;
		glm::vec2 v2;
		triangle(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2) : v0(v0), v1(v1), v2(v2) {}
	};


	std::vector<glm::vec2> squarePoints = {
		// triangle 1
		glm::vec2(0, 0), glm::vec2(300, 0), glm::vec2(0, 100),
	};

	 glm::mat4 projectionMatrix = glm::perspective(
      glm::radians(90.0f), (float)800 / (float)600, 0.1f,
      100.0f);

	  glm::mat4 viewMatrix = glm::lookAt(
		  glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	  glm::mat4 modelMatrix =
		  glm::scale(glm::mat4(1.f), glm::vec3(1, 1, 1)) *
		  glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));

	  glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	auto mesh = subdivideTriangle(octahedronPoints, 8);
	normalizeTri(mesh, glm::vec3(0, 0, 0), 2.f);

	for (auto& t : mesh) {
		auto uv1 = getUV(t.a.position);
		auto uv2 = getUV(t.b.position);
		auto uv3 = getUV(t.c.position);

		t.a.uv = uv1;
		t.b.uv = uv2;
		t.c.uv = uv3;
	}

	mdcpp::Texture texture;
	texture.loadFromFile("assets/earthmap.jpg", true);


	auto meshO = new  mdcpp::Vertices(mesh, mdcpp::RenderType::TEXTURE);
	meshO->setTexture(&texture);







	while(!window.shouldClose())
	{
		mvp *= glm::rotate(glm::mat4(1.f), glm::radians(1.f), glm::vec3(0, 1, 0));
		window.draw(square);

		square->setPos(mdcpp::Input::getMousePosition());
		window.draw(meshO, false, mvp);
		window.render();
	}

	return 0;
}
