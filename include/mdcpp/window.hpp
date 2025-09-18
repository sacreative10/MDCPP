#ifndef WINDOW_H
#define WINDOW_H

#include "mdcpp/drawables/drawables.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include <memory>
#include <queue>

namespace mdcpp {
	class Window;
}


namespace mdcpp
{

struct WindowParameters{
	uint32_t width;
	uint32_t height;
	std::string title;
};

class Window{
public:
	Window(WindowParameters params);
	Window(uint32_t width, uint32_t height);
	Window(uint32_t width, uint32_t height, std::string title);

	bool shouldClose();

	void draw(std::shared_ptr<Drawable> drawable, bool useDefaultMVP = true, glm::mat4 mvpMatrix = glm::mat4(1.f));
	void render();

	static Window& getActiveWindow();
	GLFWwindow* getWindow() const { return m_window; }
	WindowParameters& getParams() { return m_params; }

	void setClearColour(glm::vec3 colour) { m_clearColour = colour; }



	~Window();	
private:
	void init();
	bool initFramebuffer();
	void initQuad();
	void clear(glm::vec3 col);

	WindowParameters m_params;

	GLFWwindow* m_window = nullptr;
	GLuint m_framebuffer = 0;
	GLuint m_renderTexture = 0;

	GLuint m_quadVAO, m_quadVBO, m_quadEBO = 0;

	GLuint m_shaderProgram = 0;
	std::queue<std::shared_ptr<Drawable>> m_drawables;

	glm::mat4 m_mvpMatrix;

	glm::vec3 m_clearColour = glm::vec3(0.f);
};


};

#endif
