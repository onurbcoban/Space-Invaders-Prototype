#include <iostream>
#include  <glad/glad.h>
#include <GLFW/glfw3.h>
#include  <cstdint>

using namespace std;

struct Buffer
{
	size_t width, height;
	uint32_t* data;
};

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b)
{
	return(r << 24) | (g << 16) | (b << 8) | 255;;
}

void buffer_clear(Buffer* buffer, uint32_t color)
{
	for (size_t i = 0; i < buffer->width * buffer->height; ++i)
	{
		buffer->data[i] = color;
	}
}

const char* vertex_shader =
"\n"
"#version330\n"
"noperspective out vec2 TexCoord; \n"
"\n"
"void main(void){\n"
"\n"
"	 TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0; \n"
"	 TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0; \n"
"	 \n"
"	 gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
"}\n";

const char* fragment_shader =
"\n"
"#version 330\n"
"\n"
"uniform sampler2D buffer;\n"
"noperspective in vec2 TexCoord;\n"
"\n"
"void main(void){\n"
"	 outColor = texture(buffer, TexCoord).rgb;\n"
"}\n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
			return -1;
	
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	int glVersion[2] = { -1,1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[1]);

	std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;

	glViewport(0, 0, 800, 600);

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	const size_t buffer_width = 800;
	const size_t buffer_height = 600;
	
	
	uint32_t clear_color = rgb_to_uint32(0, 128, 0);
	Buffer buffer;
	buffer.width = buffer_width;
	buffer.height = buffer_height;
	buffer.data = new uint32_t[buffer.width * buffer_height];
	buffer_clear(&buffer, clear_color);

	GLuint fullscreen_triangle_vao;
	glGenVertexArrays(1, &fullscreen_triangle_vao);
	glBindVertexArray(fullscreen_triangle_vao);


	//glClearColor(0.0, 0.0, 1.0, 1.0);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
		
		

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}







