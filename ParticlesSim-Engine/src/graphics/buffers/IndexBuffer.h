#pragma once

#include <GL/glew.h>

namespace particlesSimulator {
	namespace graphics {

		class IndexBuffer
		{
		private:
			GLuint m_indexBufferID;
			GLuint m_count;;

		public:
			IndexBuffer(GLushort* data, const GLsizei count);
			IndexBuffer(GLuint* data, const GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_count; }
		};

	}
}
