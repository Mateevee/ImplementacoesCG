#include<iostream>
#include<stdlib.h>
#include<glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow* window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW OpenGL Playground", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	int image = 0;
	bool key_pressed_right = false;
	bool key_pressed_left = false;

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !key_pressed_right)
		{
			image++;
			key_pressed_right = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
			key_pressed_right = false;

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !key_pressed_left)
		{
			image--;
			key_pressed_left = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
			key_pressed_left = false;

		if (image > 3)
			image = 0;
		else if (image < 0)
			image = 3;

		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);

		glVertex2f(0.0f, 1.0f);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glEnd();

		switch (image)
		{
		case 0:
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);

			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glVertex2f(0.5f, 1.0f);
			glEnd();
			break;
		case 1:
			glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 0.0f, 0.0f);

			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glVertex2f(0.5f, 1.0f);
			glEnd();
			break;
		case 2:
			glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 0.0f, 0.0f);

			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glVertex2f(0.5f, 1.0f);
			glEnd();

			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);

			glVertex2f(0.0f, 0.0f);
			glVertex2f(-1.0f, 0.0f);
			glVertex2f(-0.5f, -1.0f);
			glEnd();
			break;
		case 3:
			glBegin(GL_LINE_STRIP);
			glColor3f(0.0f, 0.0f, 0.0f);

			glVertex2f(0.3f, 0.7f);
			glVertex2f(0.7f, 0.0f);
			glVertex2f(0.3f, -0.7f);
			glVertex2f(-0.3f, -0.7f);
			glVertex2f(-0.7f, 0.0f);
			glVertex2f(-0.3f, 0.7f);
			glEnd();
			break;

		default:
			break;
		}

		// check events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}