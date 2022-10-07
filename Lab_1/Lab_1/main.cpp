
#include "Window.h"
#include "RenderSystem.h"
#include "OBJReader.h"
#include "Material.h"

#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

const Material materials[] = 
{
	{ { 0.2125, 0.1275, 0.054 }, { 0.7140, 0.4284, 0.18144 }, { 0.3935, 0.2719, 0.1667 }, (128 * 0.2f) },
	{ { 0.0215, 0.1745, 0.0215 }, { 0.7568, 0.6142, 0.0757 }, { 0.6330, 0.7278, 0.6330 }, (128 * 0.6f) },
	{ { 0.3294, 0.2235, 0.0274 }, { 0.7804, 0.5686, 0.1137 }, { 0.9922, 0.9411, 0.8078 }, (128 * 0.218f) }
};

std::vector<Vertex> transformVertices(std::vector<Vertex> vertices, const glm::mat4& transformation)
{
	for (auto& vertex : vertices)
	{
		vertex.position = transformation * glm::vec4(vertex.position, 1.0f);
		vertex.normal = transformation * glm::vec4(vertex.normal, 0.0f);
	}

	return vertices;
}

std::pair<glm::vec3, glm::vec3> calculateAABB(const std::vector<Vertex>& vertices)
{
	std::pair<glm::vec3, glm::vec3> AABB = { vertices.front().position, vertices.front().position };

	for (const auto& vertex : vertices)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (AABB.first[i] > vertex.position[i])
			{
				AABB.first[i] = vertex.position[i];
			}

			if (AABB.second[i] < vertex.position[i])
			{
				AABB.second[i] = vertex.position[i];
			}
		}
	}

	return AABB;
}

int main()
{
	try
	{
	std::string filename;
	glm::vec3 direction;
	std::cout << "Input file to read: ";
	std::cin >> filename;
	std::cout << "Input the direction: ";
	std::cin >> direction.x >> direction.y >> direction.z;
	direction = glm::normalize(direction);

	auto mesh = OBJReader::readFile(filename);

		Window window("Computational Geometry - Lab 1", 1200, 800);
		RenderSystem renderSystem;
		renderSystem.init();

		renderSystem.setViewport(0, 0, window.getWidth(), window.getHeight());
		renderSystem.setupLight(0, glm::vec4(-1.0f, 2.5f, 10.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
		renderSystem.turnLight(0, true);

		renderSystem.setupMaterial(materials[1]);
		
		std::pair<glm::vec3, glm::vec3> meshAABB = calculateAABB(mesh);
		glm::vec3 meshCenter = meshAABB.first + ((meshAABB.second - meshAABB.first) / 2.0f);

		float time = float(glfwGetTime());
		while (!glfwWindowShouldClose(window.getGLFWHandle()))
		{
			float deltaTime = float(glfwGetTime()) - time;
			time = float(glfwGetTime());
			renderSystem.clearDisplay({ 0.3f, 0.3f, 0.3f });

			mesh = transformVertices(mesh, glm::translate(glm::mat4(1.0f), -meshCenter));
			mesh = transformVertices(mesh, glm::rotate(glm::mat4(1.0f), deltaTime, direction));
			mesh = transformVertices(mesh, glm::translate(glm::mat4(1.0f), meshCenter));

			renderSystem.setWorldMatrix(glm::mat4(1.0f));
			renderSystem.setViewMatrix(glm::lookAt(glm::vec3(0.0f, 3.0f, 7.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			renderSystem.setProjectionMatrix(glm::perspective(float(glm::radians(60.0f)), float(window.getWidth()) / float(window.getHeight()), 0.01f, 100.0f));

			renderSystem.renderTriangles(mesh);

			glfwSwapBuffers(window.getGLFWHandle());
			glfwPollEvents();
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}
