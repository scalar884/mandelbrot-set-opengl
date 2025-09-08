#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

int main()
{
	/* init glfw */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* turn off trandform window */
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	/* create a window */
	GLFWwindow* window = glfwCreateWindow(1200, 1200, "Mandelbrot set", NULL, NULL);
	if(window == NULL) 
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	/* init glew */
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		return -1;
	}
	/* pass windows size opengl */
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	shaderInit();
	/* window loop */
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
		shaderRender();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}


