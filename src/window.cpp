#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "mdcpp/drawables/drawables.hpp"
#include <mdcpp/window.hpp>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <mdcpp/utils/shaders.hpp>

static mdcpp::Window* s_Instance = nullptr;


namespace mdcpp {

	Window &Window::getActiveWindow() {
		return *s_Instance;
	}

Window::Window(WindowParameters params): m_params(params)
{
	init();
}

Window::Window(uint32_t width, uint32_t height)
{
	m_params.width = width;
	m_params.height = height;
	m_params.title = "mdcpp";
	init();
}

Window::Window(uint32_t width, uint32_t height, std::string title)
{
	m_params.width = width;
	m_params.height = height;
	m_params.title = title;
	init();
}

Window::~Window()
{
}

void Window::init()
{
	if(!glfwInit()){
		spdlog::error("Failed to initialize GLFW");
		exit(-1);
	}

	//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	
	m_window = glfwCreateWindow(m_params.width, m_params.height, m_params.title.c_str(), nullptr, nullptr);
	if(!m_window){
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }	

	glViewport(0, 0, m_params.width, m_params.height);

	spdlog::info("GLFW Window created");

	if(!initFramebuffer()){
		glfwDestroyWindow(m_window);
		glfwTerminate();
		exit(-1);
	}

	if(!loadShader("shaders/screen_vert.glsl", "shaders/screen_frag.glsl")){
		glfwDestroyWindow(m_window);
		glfwTerminate();
		exit(-1);
	}

	initQuad();

	
	m_mvpMatrix = glm::ortho(0.0f, (float)m_params.width, (float)m_params.height, 0.f) * glm::translate(glm::mat4(1.f), glm::vec3(0.5 * m_params.width, 0.5 * m_params.height, 0.f));

	s_Instance = this;
}


bool Window::initFramebuffer()
{
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	glGenTextures(1, &m_renderTexture);
	glBindTexture(GL_TEXTURE_2D, m_renderTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_params.width, m_params.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		spdlog::error("Failed to create framebuffer");
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void Window::initQuad()
{
	float quadVertices[] = {
        // positions     // texCoords
        -1.0f,  1.0f,     0.0f, 1.0f,
        -1.0f, -1.0f,     0.0f, 0.0f,
         1.0f, -1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,     1.0f, 1.0f
    };
    unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };


	glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);
    glGenBuffers(1, &m_quadEBO);

    glBindVertexArray(m_quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}


// hacky but it works
void Window::draw(std::shared_ptr<Drawable> drawable, bool useDefaultMVP, glm::mat4 mvpMatrix)
{
	if(useDefaultMVP){
		drawable->setMVPMatrix(m_mvpMatrix);
		m_drawables.push(drawable);
	}else{
		drawable->setMVPMatrix(mvpMatrix);
		m_drawables.push(drawable);
	}
}

void Window::clear(glm::vec3 col)
{
	glClearColor(col.r, col.g, col.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::render()
{
	clear(m_clearColour);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glViewport(0, 0, m_params.width, m_params.height);

	glUseProgram(m_shaderProgram);

	glBindVertexArray(m_quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_params.width, m_params.height);
	
	while(!m_drawables.empty()){
		m_drawables.front()->draw();
		m_drawables.pop();
	}

	glfwSwapBuffers(m_window);
	glfwPollEvents();
};

}
