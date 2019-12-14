#include "IndexBuffer.h"

namespace particlesSimulator {
	namespace graphics {

		IndexBuffer::IndexBuffer(GLushort* data, const GLsizei count)
			:m_count(count)
		{
			glGenBuffers(1, &m_indexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::IndexBuffer(GLuint* data, const GLsizei count)
			:m_count(count)
		{
			glGenBuffers(1, &m_indexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_indexBufferID);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		}
		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}