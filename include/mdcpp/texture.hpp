#ifndef MDCPP_TEXTURE_HPP
#define MDCPP_TEXTURE_HPP
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>


namespace mdcpp {

class Texture {

public:

	Texture() = default;
	~Texture();
	bool loadFromFile(std::string path, bool flip = false);
	void bind(GLenum texUnit = GL_TEXTURE0) const;
	void unbind();
	void setColour(glm::vec3 colour) { m_colour = colour; }

	GLuint getTextureID() { return m_texID; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	int getChannels() { return m_channels; }


private:

	uint32_t m_width, m_height = 0;
	int m_channels = 0;

	GLuint m_texID;
	glm::vec3 m_colour = glm::vec3(1.0f, 1.0f, 1.0f); // default white (can be changed and used in exchange of a texture)

};

};


#endif
