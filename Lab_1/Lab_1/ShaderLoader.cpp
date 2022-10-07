#include "ShaderLoader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace
{
	void checkCompileErrors(GLuint shaderId)
	{
		GLint success;
		char infoLog[1024];

		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
			throw std::runtime_error("Compilation failed: " + std::string(infoLog));
		}
	}

	GLuint createShader(const char* code, GLenum shaderType)
	{
		GLuint shaderId = glCreateShader(shaderType);
		glShaderSource(shaderId, 1, &code, NULL);
		glCompileShader(shaderId);
		checkCompileErrors(shaderId);

		return shaderId;
	}

	void checkLinkErrors(GLuint programId)
	{
		GLint success;
		char infoLog[1024];

		glGetShaderiv(programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(programId, 1024, NULL, infoLog);
			throw std::runtime_error("Linking failed: " + std::string(infoLog));
		}
	}
}

GLuint ShaderLoader::load(const std::string& filename, GLenum shaderType)
{
	if (!std::filesystem::exists(std::filesystem::path(filename)))
		throw std::invalid_argument("Can't load shader from " + filename);

	std::ifstream file(filename);
	std::stringstream code;

	code << file.rdbuf();

	return createShader(code.str().c_str(), shaderType);
}

GLuint ShaderLoader::linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	checkLinkErrors(programId);

	return programId;
}
