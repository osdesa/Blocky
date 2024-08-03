#include "core/window.h"
#include "logger.h"

#include <iostream>

void Window::InstallMainCallback()
{
	if (window != nullptr)
	{
		glfwSetKeyCallback(window, Input::keyCallback);
		glfwSetCursorPosCallback(window, Input::mouseCallback);
		glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
	}
}

void Window::Close()
{
	if (window != nullptr) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

Window* Window::CreateWindow(int width, int height, const char* title, bool fullScreen)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window* res = new Window();
	GLFWmonitor* primaryMonitor = fullScreen ? glfwGetPrimaryMonitor() : nullptr;
	res->window = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);
	if (res->window == nullptr)
	{
		Logger::output(FATAL, "Failed to create GLFW window");
		glfwTerminate();
		return nullptr;
	}
	glfwSetInputMode(res->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwMakeContextCurrent(res->window);

	return res;
}

void Window::FreeWindow(Window* window)
{
	if (window) {
		glfwDestroyWindow(window->window);
		delete window;
	}
}
