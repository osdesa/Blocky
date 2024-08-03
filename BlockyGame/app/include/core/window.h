#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/input.h"

class Window
{
public:
	int windowWidth;
	int windowHeight;
	GLFWwindow* window;
	
	void InstallMainCallback();
	void Close();

	static Window* CreateWindow(int width, int height, const char* title, bool fullScreen = false);
	static void FreeWindow(Window* window);
};