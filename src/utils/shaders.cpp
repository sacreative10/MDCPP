
#include <mdcpp/utils/shaders.hpp>
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>


GLuint compileShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		std::string typeName = (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
		throw std::runtime_error("Shader Compilation Failed (" + typeName + "):\n" + log);
	}

	return shader;
}

std::string readFile(const std::string& path) {
	std::ifstream file(path);
	if (!file)
		throw std::runtime_error("Failed to open file: " + path);

	spdlog::info("Reading file: {}", path);

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint loadShader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::string vertexCode = readFile(vertexShaderPath);
    std::string fragmentCode = readFile(fragmentShaderPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
		spdlog::error("Shader Linking Failed:\n{}", log);
		return false;
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	return shaderProgram;
}
