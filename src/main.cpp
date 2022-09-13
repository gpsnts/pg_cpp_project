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

	std::cout << "Foo " << std::endl;

	typedef struct Vertex {
		GLfloat coords[3];
	} VecXYZ;

	const GLubyte* renderer;
	const GLubyte* version;
	GLuint vao, vao2;
	GLuint vbo, vbo2;

	VecXYZ points[3];
	points[0].coords[0]=0.0f;
	points[0].coords[1]=0.75f;
	points[0].coords[2]=0.0f;
	points[1].coords[0]=0.5f;
	points[1].coords[1]=-0.5f;
	points[1].coords[2]=0.0f;
	points[2].coords[0]=-0.5f;
	points[2].coords[1]=-0.5f;
	points[2].coords[2]=0.0f;
	
	GLfloat colors[] = {
	  1.0f, 0.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
	  0.0f, 0.0f, 1.0f
	};

	float matrix[] = {
		0.707106781186548f, -0.707106781186548f, 0.0f, 0.0f,
		0.707106781186548f, 0.707106781186548f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.1f, 0.0f, 0.0f, 1.0f
	};

	const char* vertex_shader =
	"#version 410\n"
	"layout(location=0) in vec3 vp;"
	"layout(location=1) in vec3 vc;"
	"uniform mat4 matrix;"
	"out vec3 color;"
	"void main () {"
	"   color = vc;"
	"	gl_Position = matrix * vec4 (vp, 1.0);"
	"}";

	const char* fragment_shader =
	"#version 410\n"
    "in vec3 color;"
	"out vec4 frag_color;"
	"void main () {"
	"	frag_color = vec4 (color, 1.0);"
	"}";

	GLuint vs, fs, fs2;
	GLuint shader_programme, shader_programme2;

	renderer = glGetString(GL_RENDERER); /* get renderer string */
	version = glGetString(GL_VERSION); /* version as a string */
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	glDepthFunc(GL_LESS);/*depth-testing interprets a smaller value as "closer"*/

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint colorsVBO;
	glGenBuffers (1, &colorsVBO);
	glBindBuffer (GL_ARRAY_BUFFER, colorsVBO);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
		
	vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);
	
	shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);
	
	int matrixLocation = glGetUniformLocation(shader_programme, "matrix");

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
	
	float speed = 1.0f;
	float lastPosition = 0.0f;
	glUseProgram (shader_programme);

	while(!glfwWindowShouldClose(app->get_window()))
	{
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		if(elapsedSeconds > 0.05) {
			previousSeconds = currentSeconds;
			if(fabs(lastPosition) > 1.0f){
				speed = -speed;
			}
			matrix[12] = elapsedSeconds * speed + lastPosition;
			lastPosition = matrix[12];
		}

		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBindVertexArray (vao);
		glDrawArrays (GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(app->get_window());
	}
	

  // auto foo = GlUtils::stbi_load_image("/home/usr/Projects/pg_cpp_project/src/textures/block.png", GL_TRUE);

  // GLfloat verts[] = {
  //   // Positions               // Colors (R|G|B)
  //    0.5f, -0.5f, 0.0f,        1.0f, 0.0f, 0.0f, // Bottom Right
  //   -0.5f, -0.5f, 0.0f,        0.0f, 1.0f, 0.0f, // Bottom Left
  //    0.0f,  0.5f, 0.0f,        0.0f, 0.0f, 1.0f // Top
  // };

  // GLuint VBO, VAO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // glBindVertexArray(VAO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  
  // // Posições:
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  // glEnableVertexAttribArray(0);
  
  // // Cores:
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  // glEnableVertexAttribArray(1);

  // const char* vertex_shader =
  //   "#version 410\n"
  //   "layout(location=0) in vec3 vp;"
  //   "layout(location=1) in vec3 vc;"
  //   "out vec3 color;"
  //   "void main () {"
  //   " color = vc;"
  //   " gl_Position = vec4 (vp, 1.0);"
  //   "}";

  // const char* fragment_shader =
  //   "#version 410\n"
  //   "in vec3 color;"
  //   "out vec4 frag_color;"
  //   "void main () {"
  //   " frag_color = vec4 (color, 1.0);"
  //   "}";

  // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vs, 1, &vertex_shader, NULL);
  // glCompileShader(vs);

  // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  // glShaderSource(fs, 1, &fragment_shader, NULL);
  // glCompileShader(fs);

  // GLuint shader_programme = glCreateProgram ();
  // glAttachShader(shader_programme, fs);
  // glAttachShader(shader_programme, vs);
  // glLinkProgram(shader_programme);
  // glDetachShader(shader_programme, fs);
  // glDetachShader(shader_programme, vs);

  // glUseProgram (shader_programme);

  // while(!glfwWindowShouldClose(app->get_window()))
	// {
  //   Application::frames_per_second(app->get_window());

  //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  //   glBindVertexArray(VAO);
  //   glDrawArrays(GL_TRIANGLES, 0, 3);
    
  //   glfwSwapBuffers(app->get_window());
  //   glfwPollEvents();
  // }

  glfwTerminate();
  return EXIT_SUCCESS;
}