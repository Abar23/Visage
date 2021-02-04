#include "RenderWindow.h"

#include <iostream>
#include <glad/glad.h>

namespace Visage
{
	namespace Rendering
	{
		RenderWindow::RenderWindow()
		{
			if (!glfwInit())
			{
				std::cout << "GLFW could not be intialized!" << std::endl;
				exit(EXIT_FAILURE);
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			window = glfwCreateWindow(640, 400, "Test window", NULL, NULL);

			if (window == NULL)
			{
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			glfwMakeContextCurrent(window);
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Glad could not init OpenGL" << std::endl;
				exit(EXIT_FAILURE);
			}
			glfwSwapInterval(1);
		}

		RenderWindow::~RenderWindow()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		void RenderWindow::Run()
		{
			while (!glfwWindowShouldClose(window))
			{
				glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glfwPollEvents();
				glfwSwapBuffers(window);
			}
		}
	}
}