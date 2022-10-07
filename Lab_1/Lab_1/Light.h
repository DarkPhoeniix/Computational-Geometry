#pragma once

#include "Shader.h"

#include <glm.hpp>

class Light
{
public:
	Light() = default;
	Light(std::uint32_t index, const glm::vec4 position, const glm::vec3 ambient, const glm::vec3& diffuse, const glm::vec3& specular);

	void render(const Shader& shader) const;
	
	std::uint32_t index;

	glm::vec4 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	bool enable;
};
