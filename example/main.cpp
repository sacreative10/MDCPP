
#include <mdcpp/window.hpp>
#include <mdcpp/drawables/polygon.hpp>
#include <mdcpp/drawables/vertex.hpp>
#include <mdcpp/drawables/line.hpp>
#include <glm/ext.hpp>

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

	std::vector<glm::vec3> octahedronPoints = {
		// top
		glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1),
		glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1),
		glm::vec3(0, -1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1),
		glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1),
		// bottom
		glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1),
		glm::vec3(1, 0, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, -1),
		glm::vec3(0, -1, 0), glm::vec3(-1, 0, 0), glm::vec3(0, 0, -1),
		glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1),
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


	auto vertexModel = new mdcpp::Vertices(octahedronPoints);

	auto line = new mdcpp::Line(glm::vec2(0, 0), glm::vec2(100, 100));

	auto polygon = new mdcpp::ConvexPolygon(squarePoints, 2.f, glm::vec3(1.f, 0.f, 0.f), false);




	while(!window.shouldClose())
	{
		window.draw(vertexModel, false, mvp);
		mvp *= glm::rotate(glm::mat4(1.f), glm::radians(1.f), glm::vec3(0, 1, 0));
		window.draw(line);
		window.draw(square);
		window.draw(polygon);
		window.render();
	}

	return 0;
}
