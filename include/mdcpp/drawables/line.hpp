#ifndef LINE_H
#define LINE_H

#include "drawables.hpp"

namespace mdcpp {
class Line : public Drawable
{
public:
	Line(glm::vec2 start, glm::vec2 end, float thickness = 1.0f, glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f));

	void updatePoints(glm::vec2 start, glm::vec2 end);

private:
	void draw() override;
	void updateBuffer();
	void setup() override;
	
	glm::vec2 m_start, m_end;
};
};


#endif
