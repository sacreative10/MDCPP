#ifndef DRAWABLES_H
#define DRAWABLES_H

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace mdcpp {
	
// A base class that is drawable by the window
class Drawable {
public:
	// To be called by the window NOT the user
	virtual void draw() = 0;

	const virtual inline void setMVPMatrix(glm::mat4 mvpMatrix) {
		m_mvpMatrix = mvpMatrix;
	}
	const virtual inline void setThickness(int thickness) {
		m_thickness = thickness;
	}
	const virtual inline void setColour(glm::vec3 colour) {
		m_colour = colour;
	}
	const virtual inline void setFill(bool fill) {
		m_fill = fill;
	}

	Drawable() {
		m_thickness = 1.f;
		m_colour = glm::vec3(1.f);
		m_fill = true;
	}
	Drawable(float thickness, glm::vec3 colour, bool fill) {
		m_thickness = thickness;
		m_colour = colour;
		m_fill = fill;
	}
protected:
	// call this in the ctor
	virtual void setup() = 0;

	GLuint m_shaderProgram = 0;
	GLuint m_VAO, m_VBO, m_EBO = 0;

	glm::mat4 m_mvpMatrix;
	// Default(ish) attributes
	float m_thickness = 1.f;
	glm::vec3 m_colour = glm::vec3(1.f);
	bool m_fill = true;

};


};


#endif
