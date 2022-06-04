#include "Window.h"
#include "IOHandler.h"
#include "../InitializationData.h"

namespace particlesSimulator {
	namespace graphics {

		void windowResize(GLFWwindow* window, int width, int height);
		bool heightChange = false;

		Window::Window(const char* name, int width, int height)
			:m_title(name), m_width(width), m_orig_width(width), m_orig_height(height), m_height(height), m_glfWindow(nullptr)
		{
			if (!init()) {
				glfwTerminate();
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				PRINT_ERROR("OpenGL Error!", error);
			}

			if (heightChange) {
				glfwGetWindowSize(m_glfWindow, &m_width, &m_height);
				heightChange = false;
			}
			glfwPollEvents();

			// set the vertical sync to be on or off from 'initializationData.h' file.
#if defined(VSYNC)
			glfwSwapInterval(1);
#else
			glfwSwapInterval(0);
#endif
			glfwSwapBuffers(m_glfWindow);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_glfWindow);
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::init()
		{
			// if there was an error initializing the window print an error
			if (!glfwInit()) {
				PRINT_ERROR("Failed to initialize GLFW!", "");
				return false;
			}

			m_glfWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

			// if the window could not be created for some reason print an error message.
			if (!m_glfWindow) {
				glfwTerminate();
				PRINT_ERROR("Failed to create GLFW window!", "");
				return false;
			}

			glfwMakeContextCurrent(m_glfWindow);
			glfwSwapInterval(1);
			glfwSetWindowSizeCallback(m_glfWindow, windowResize);

			if (glewInit() != GLEW_OK) {
				PRINT_ERROR("GLEW cannot be initialized!", "");
			}

			return true;
		}

		void windowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			heightChange = true;
		}
	}
}
