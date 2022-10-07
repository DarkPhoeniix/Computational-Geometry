#pragma once

#include "Vertex.h"
#include "Shader.h"
#include "Material.h"
#include "Light.h"

#include <vector>
#include <cstdint>
#include <memory>
#include <map>

#include <glm.hpp>

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void init();

	void clearDisplay(glm::vec3 color);

	void setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) const;
	void renderTriangles(const std::vector<Vertex>& vertices);

	void setupMaterial(const Material& material);
	void setupLight(std::uint32_t index, const glm::vec4 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3& specular);
	void turnLight(std::uint32_t index, bool enable);

	void setWorldMatrix(const glm::mat4& world);
	const glm::mat4& getWorldMatrix() const;

	void setViewMatrix(const glm::mat4& view);
	const glm::mat4& getViewMatrix() const;

	void setProjectionMatrix(const glm::mat4& projection);
	const glm::mat4 getProjectionMatrix() const;

private:
	void bindBuffers(const std::vector<Vertex>& vertices);

	std::unique_ptr<Shader> shader;

	std::map<std::uint32_t, Light> lights;

	glm::mat4 world;
	glm::mat4 view;
	glm::mat4 projection;

	GLuint VAO, VBO;
};

