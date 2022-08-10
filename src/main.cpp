#define STB_IMAGE_IMPLEMENTATION

#include "headers/gl_utils.hpp"
#include "headers/application.hpp"

int main(int argc, char** argv)
{
  GLint HEIGHT = 768;
	GLint WIDTH = 1366;
	const GLchar *APP_NAME = "";

	Application *app = new Application(HEIGHT, WIDTH, APP_NAME);


  if (!app->init())
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

  // auto foo = GlUtils::stbi_load_image("/home/messer/Projects/pg_cpp/src/textures/block.png", GL_TRUE);

  GLfloat verts[] = {
    // Positions               // Colors (R|G|B)
     0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f,        0.0f, 1.0f, 0.0f, // Bottom Left
     0.0f,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f // Top
  };

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  
  // Posições:
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  // Cores:
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  const char* vertex_shader =
    "#version 410\n"
    "layout(location=0) in vec3 vp;"
    "layout(location=1) in vec3 vc;"
    "out vec3 color;"
    "void main () {"
    " color = vc;"
    " gl_Position = vec4 (vp, 1.0);"
    "}";

  const char* fragment_shader =
    "#version 410\n"
    "in vec3 color;"
    "out vec4 frag_color;"
    "void main () {"
    " frag_color = vec4 (color, 1.0);"
    "}";

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram ();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);
  glDetachShader(shader_programme, fs);
  glDetachShader(shader_programme, vs);

  glUseProgram (shader_programme);

  while(!glfwWindowShouldClose(app->get_window()))
	{
    Application::frames_per_second(app->get_window());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(app->get_window());
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}