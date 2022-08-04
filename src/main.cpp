#include <string>

#include "headers/gl_utils.hpp"
#include "headers/application.hpp"


int main(int argc, char** argv)
{
	GlUtils::debug_print<std::string>("DEBUG MODE!");

  GLint HEIGHT = 768;
	GLint WIDTH = 1366;
	const GLchar *APP_NAME = "TEST";

	Application *app = new Application(HEIGHT, WIDTH, APP_NAME);


  if (!app->init())
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

  auto foo = GlUtils::stbi_load_image("/home/messer/Projects/pg_cpp/src/textures/block.png", GL_TRUE);

  GlUtils::debug_print(foo);

  while(!glfwWindowShouldClose(app->get_window()))
	{
    Application::frames_per_second(app->get_window());
    
    glfwPollEvents();
    glfwSwapBuffers(app->get_window());
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}