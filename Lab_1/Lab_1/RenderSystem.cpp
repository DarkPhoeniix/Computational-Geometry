#include "RenderSystem.h"

RenderSystem::RenderSystem()
	: world(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)), VAO(0), VBO(0)
{	}

RenderSystem::~RenderSystem()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void RenderSystem::init()
{
	shader = std::make_unique<Shader>("resources\\shader.vs", "resources\\shader.fs");

	glEnable(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void RenderSystem::clearDisplay(glm::vec3 color)
{
	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) const
{
	glViewport(x, y, width, height);
}

void RenderSystem::renderTriangles(const std::vector<Vertex>& vertices)
{
	shader->use();
	bindBuffers(vertices);

	shader->setMat4("world", world);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	glm::vec3 viewPosition = glm::vec3(glm::inverse(view)[3]);
	shader->setVec3("viewPosition", viewPosition);

	shader->setInt("lightsNumber", lights.size());
	for (const auto& [index, light] : lights)
	{
		light.render(*shader);
	}

	glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(vertices.size()));
	glBindVertexArray(0);
}

void RenderSystem::setupMaterial(const Material& material)
{
	shader->use();
	shader->setVec3("material.ambient", material.ambient);
	shader->setVec3("material.diffuse", material.diffuse);
	shader->setVec3("material.specular", material.specular);
	shader->setFloat("material.shininess", material.shininess);
}

void RenderSystem::setupLight(std::uint32_t index, const glm::vec4 position, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3& specular)
{
	if (lights.size() < 8)
	{
		lights[index] = Light(index, position, ambient, diffuse, specular);
	}
}

void RenderSystem::turnLight(std::uint32_t index, bool enable)
{
	lights[index].enable = enable;
}

void RenderSystem::setWorldMatrix(const glm::mat4& world)
{
	this->world = world;
}

const glm::mat4& RenderSystem::getWorldMatrix() const
{
	return world;
}

void RenderSystem::setViewMatrix(const glm::mat4& view)
{
	this->view = view;
}

const glm::mat4& RenderSystem::getViewMatrix() const
{
	return view;
}

void RenderSystem::setProjectionMatrix(const glm::mat4& projection)
{
	this->projection = projection;
}

const glm::mat4 RenderSystem::getProjectionMatrix() const
{
	return projection;
}

void RenderSystem::bindBuffers(const std::vector<Vertex>& vertices)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: vertices.data() ?
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}
