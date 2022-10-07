#include "Window.h"

Window::Window(const std::string& title, std::uint32_t width, std::uint32_t height)
	: width(width), height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(handle);

	static bool initGLAD = false;
	if (!initGLAD)
	{
		initGLAD = true;
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
}

Window::~Window()
{
	glfwDestroyWindow(handle);
	glfwTerminate();
}

std::uint32_t Window::getWidth() const
{
	return width;
}

std::uint32_t Window::getHeight() const
{
	return height;
}

GLFWwindow* Window::getGLFWHandle() const
{
	return handle;
}
