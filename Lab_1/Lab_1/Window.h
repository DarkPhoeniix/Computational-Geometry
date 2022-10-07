#pragma once

#include <cstdint>
#include <string>

#include "glad/glad.h"
#include <glfw3.h>

class Window
{
public:
	Window(const std::string& title, std::uint32_t width, std::uint32_t height);
	~Window();

	std::uint32_t getWidth() const;
	std::uint32_t getHeight() const;

	GLFWwindow* getGLFWHandle() const;

private:
	GLFWwindow* handle;

	std::uint32_t width;
	std::uint32_t height;
};
