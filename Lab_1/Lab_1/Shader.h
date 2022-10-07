#pragma once

#include <string>

#include <glad/glad.h>
#include <glm.hpp>

class Shader
{
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	void use() const;

	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;

private:
	GLint id;
	GLint VAO, VBO;
};
