#include "Display.h"
#include <iostream>
#include <vector>

#include <chrono>
#include <Windows.h>

Display::Display(int window_width, int window_height)
	:window(nullptr), window_width(window_width), window_height(window_height)
{
	initialize_window();
}

Display::~Display()
{
}

void Display::initialize_window()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Failed to init!" << std::endl;
		glfwTerminate();

		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(window_width, window_height, "Croc Craft", NULL, NULL);
	
	if (!window)
	{
		std::cout << "GLFW failed to create window! \n";
		glfwTerminate();
		return;
	}

	glfwGetFramebufferSize(window, &buffer_width, &buffer_height);

	glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);

	create_callbacks();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "error initializing GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, buffer_width, buffer_height);
	glfwSetWindowUserPointer(window, this);

}

void Display::swap_buffers()
{
	glfwSwapBuffers(window);
}

void Display::clear_color(int r, int g, int b, int a)
{
	glClearColor(r, g, b, a);
}

void Display::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


bool Display::should_close()
{
	return glfwWindowShouldClose(window);
}


void Display::set_window_pos(int pos_x, int pos_y)
{
	glfwSetWindowPos(window, pos_x, pos_y);
}

void Display::create_callbacks()
{
	glfwSetKeyCallback(window, Display::handle_keys);
	glfwSetFramebufferSizeCallback(window, Display::framebuffer_size_callback);
}

void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Display* display = static_cast<Display*>(glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);

	display->window_width = width;
	display->window_height = height;
}

void Display::handle_keys(GLFWwindow* window, int key, int code, int action, int mode)
{
Display* display = static_cast<Display*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}