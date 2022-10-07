#include "Shader.h"

#include "ShaderLoader.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	: VAO(0), VBO(0)
{
	GLuint vertex = ShaderLoader::load(vertexShader, GL_VERTEX_SHADER);
	GLuint fragment = ShaderLoader::load(fragmentShader, GL_FRAGMENT_SHADER);

	id = ShaderLoader::linkProgram(vertex, fragment);

	//glDeleteShader(vertex);
	//glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use() const
{
	glUseProgram(id);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
