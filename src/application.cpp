#include "headers/application.hpp"

bool Application::init_glfw()
{
	if (!glfwInit())
	{
		std::cerr << "Cann't init GLFW" << std::endl;;
		return false;
	}
	return true;
}

void Application::set_profile()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

bool Application::validate_window(GLFWwindow *window)
{
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	return true;
}

bool Application::init_glad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	return true;
}

void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::frames_per_second(GLFWwindow *window)
{
	static double previous = 0.0;
	static int count = 0;
	double elapsed, current = glfwGetTime();

	elapsed = current - previous;

	if (elapsed > 1.0f)
	{
		previous = current;
		double
			frames_per_second 	= (double) count / elapsed,
			millis_per_frame 		=	1000.0 / frames_per_second;

			std::ostringstream out;
			out.precision(3);

			out << std::fixed
					<< "FPS: " << frames_per_second << " "
					<< "Frame time " << millis_per_frame << " ";

			glfwSetWindowTitle(window, out.str().c_str());

			count = 0;
	}

	count++;
}

void Application::process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

GLFWwindow *Application::get_window()
{
	return window;
}

bool Application::init()
{
	if (!init_glfw()) return false;
	set_profile();
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!validate_window(window)) return false;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Application::framebuffer_size_callback);
	if (!init_glad()) return false;
	return true;
}

Application::Application(int s_width, int s_height, std::string s_name)
{
	width = s_width;
	height = s_height;
	name = s_name;
}