#include "Window.h"
#include "IOHandler.h"

namespace particlesSimulator {
	namespace graphics {

		void windowResize(GLFWwindow* window, int width, int height);
		bool heightChange = false;

		Window::Window(const char* name, int width, int height)
			:m_Title(name), m_Width(width), m_Height(height), m_GLFWindow(nullptr)
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
				glfwGetWindowSize(m_GLFWindow, &m_Width, &m_Height);
				heightChange = false;
			}
			glfwPollEvents();
			glfwSwapInterval(0);
			glfwSwapBuffers(m_GLFWindow);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_GLFWindow);
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::init()
		{
			if (!glfwInit()) {
				PRINT_ERROR("Failed to initialize GLFW!", "");
				return false;
			}

			m_GLFWindow = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_GLFWindow) {
				glfwTerminate();
				PRINT_ERROR("Failed to create GLFW window!", "");
				return false;
			}

			glfwMakeContextCurrent(m_GLFWindow);
			glfwSwapInterval(1);
			glfwSetWindowSizeCallback(m_GLFWindow, windowResize);

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
