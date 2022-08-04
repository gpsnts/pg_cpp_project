#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

#include <iostream>
#include <sstream>
#include <string>

class Application
{
private:
	GLFWwindow *window;
	std::string name;
	int width, height;

	Application () {}

	void static framebuffer_size_callback(
		GLFWwindow *window,
		int width,
		int height
	);

	bool init_glfw();
	void set_profile();
	bool validate_window(GLFWwindow *window);
	bool init_glad();
public:
	Application (int s_width, int s_height, std::string s_name);
	
	void static frames_per_second(GLFWwindow *window);
	void static process_input(GLFWwindow *window);
	bool init();
	GLFWwindow *get_window();
};

#endif // __APPLICATION_HPP__