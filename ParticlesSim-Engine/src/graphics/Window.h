#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace particlesSimulator
{
	namespace graphics
	{
		class Window
		{
		private:
			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_GLFWindow;

		public:
			Window(const char* name, int width, int height);
			~Window();

			void Update();
			bool Closed() const;
			void Clear() const;

			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }

		private:
			bool Init();
		};
	}

}
