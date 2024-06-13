#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

const int MAX_GROUND_VALUE = 575;

class Display
{
public:
	Display(int window_width, int window_height);
	~Display();

	void initialize_window();

	void swap_buffers();

	void clear_color(int r, int g, int b, int a);
	void clear();

	bool should_close();

	GLFWwindow* get_window() { return window; };

	int get_buffer_width() { return buffer_width; };
	int get_buffer_height() { return buffer_height; };

	const GLFWvidmode* get_mode() { return mode; }; 

	void set_window_pos(int pos_x, int pos_y);

	bool* get_keys() { return keys; }
	float get_mouse_x_change();
	float get_mouse_y_change();

private:
	GLFWwindow* window;
	const GLFWvidmode* mode;
	
	unsigned int window_width;
	unsigned int window_height;

	int buffer_width;
	int buffer_height;


	bool keys[1024];

	float last_mouse_x;
	float last_mouse_y;
	float mouse_x_change;
	float mouse_y_change;
	bool mouse_first_move;
private:

	void create_callbacks();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static void handle_keys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handle_mouse(GLFWwindow* window, double x_pos, double y_pos);

};

