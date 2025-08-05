#ifndef POLYGON_H
#define POLYGON_H

#include <mdcpp/drawables/drawables.hpp>


namespace mdcpp {

class ConvexPolygon : public Drawable {
public:

	ConvexPolygon(std::vector<glm::vec2> vertices, float thickness = 2.f, glm::vec3 colour = glm::vec3(1.f), bool fill = false);

	void draw() override;
	void updateBuffer(const std::vector<glm::vec2>& vertices = std::vector<glm::vec2>());
private:
	void setup() override;

	std::vector<glm::vec2> m_vertices;
	int m_indexCount;
};


class Quad : public Drawable {
public:
	Quad(glm::vec2 pos, float width, float height, float thickness = 2.f, glm::vec3 colour=glm::vec3(1.0f, 1.0f, 1.0f), bool fill = false);

	void setPos(glm::vec2 pos);
	const void setMVPMatrix(glm::mat4 mvpMatrix) override {
		m_polygon->setMVPMatrix(mvpMatrix);
	}
private:
	void setup() override;
	void draw() override;
	void updateBuffer();
	
	glm::vec2 m_pos;
	float m_width;
	float m_height;

	ConvexPolygon* m_polygon = nullptr;
	std::vector<glm::vec2> m_vertices;

};
};


#endif
