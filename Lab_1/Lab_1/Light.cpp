#include "Light.h"

Light::Light(std::uint32_t index, const glm::vec4 position, const glm::vec3 ambient, const glm::vec3& diffuse, const glm::vec3& specular)
	: index(index), position(position), ambient(ambient), diffuse(diffuse), specular(specular), enable(false)
{	}

void Light::render(const Shader& shader) const
{
	if (enable)
	{
		shader.setVec4(std::string("lights[" + std::to_string(index) + "].position"), position);
		shader.setVec3(std::string("lights[" + std::to_string(index) + "].ambient"), ambient);
		shader.setVec3(std::string("lights[" + std::to_string(index) + "].diffuse"), diffuse);
		shader.setVec3(std::string("lights[" + std::to_string(index) + "].specular"), specular);
	}
}
