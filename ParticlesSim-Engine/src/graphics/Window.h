#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace particlesSimulator {
	namespace graphics {
		class Window
		{
		private:
			const char* m_title;
			int m_width, m_height;
			int m_orig_width, m_orig_height;
			GLFWwindow* m_glfWindow;

		public:
			Window(const char* name, int width, int height);
			~Window();

			void update();
			bool closed() const;
			void clear() const;

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }

			inline int getOrigWidth() const { return m_orig_width; }
			inline int getOrigHeignt() const { return m_orig_height; }

		private:
			bool init();
		};
	}
}
