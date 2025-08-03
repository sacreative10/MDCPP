
#include <mdcpp/texture.hpp>
#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace mdcpp {
Texture::~Texture()
{
	if (m_texID != 0)
		glDeleteTextures(1, &m_texID);
}

bool Texture::loadFromFile(std::string path, bool flip)
{
	if(flip)
		stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(),(int*) &m_width,(int*) &m_height, &m_channels, 0);
	if (!data) {
		spdlog::error("Failed to load texture: {}", path);
		return false;
	}

	GLenum format = (m_channels == 4) ? GL_RGBA : GL_RGB;

	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_2D, m_texID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	return true;
}

void Texture::bind(GLenum texUnit) const
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, m_texID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


};
