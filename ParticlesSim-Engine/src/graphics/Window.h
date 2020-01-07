#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace particlesSimulator {
	namespace graphics {
		class Window
		{
		private:
			// name off the window.
			const char* m_title;
			// width and height of the window in pixels, these values update when the window is resized.
			int m_width, m_height;
			// original width and height of the window.
			int m_orig_width, m_orig_height;
			// glww window object.
			GLFWwindow* m_glfWindow;

		public:

			/// <summary>
			/// Initializes a new instance of the <see cref="Window"/> class.
			/// </summary>
			/// <param name="name">The name of the window</param>
			/// <param name="width">The width of the window in pixels.</param>
			/// <param name="height">The height of the window in pixels.</param>
			Window(const char* name, int width, int height);
			~Window();
			
			/// <summary>
			/// Updates the content of the window.
			/// </summary>
			void update();			

			/// <summary>
			/// checks if the window is closed.
			/// </summary>
			/// <returns></returns>
			bool closed() const;			

			/// <summary>
			/// Clears this the content of the window.
			/// </summary>
			void clear() const;

			/// <summary>
			/// Gets the width.
			/// </summary>
			/// <returns></returns>
			inline int getWidth() const { return m_width; }

			/// <summary>
			/// Gets the height.
			/// </summary>
			/// <returns></returns>
			inline int getHeight() const { return m_height; }

			/// <summary>
			/// Gets the width of the original.
			/// </summary>
			/// <returns></returns>
			inline int getOrigWidth() const { return m_orig_width; }

			/// <summary>
			/// Gets the original heignt.
			/// </summary>
			/// <returns></returns>
			inline int getOrigHeignt() const { return m_orig_height; }

		private:			
			/// <summary>
			/// Initializes the window.
			/// </summary>
			/// <returns></returns>
			bool init();
		};
	}
}
