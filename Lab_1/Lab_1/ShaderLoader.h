#pragma once

#include "Shader.h"

class ShaderLoader
{
public:
	static GLuint load(const std::string& filename, GLenum shaderType);
	static GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
};
