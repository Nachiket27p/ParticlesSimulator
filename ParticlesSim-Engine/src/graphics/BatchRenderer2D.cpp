#include "BatchRenderer2D.h"


namespace particlesSimulator {
	namespace graphics {

		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_indexBuffer;
			glDeleteBuffers(1, &m_vertexBuffer);
		}

		inline void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_vertexArray);
			glGenBuffers(1, &m_vertexBuffer);

			glBindVertexArray(m_vertexArray);

			glGenBuffers(1, &m_vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			// tell opengl the locations at which each attribute is located in the struct/sptire data.
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::vertex)));
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			//GLushort* indices = new GLushort[RENDERER_INDICES_SIZE];
			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

			// set up the index vector to render squares.
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {

				indices[i] = 0 + offset;
				indices[i + 1] = 1 + offset;
				indices[i + 2] = 2 + offset;
				indices[i + 3] = 2 + offset;
				indices[i + 4] = 3 + offset;
				indices[i + 5] = 0 + offset;

				offset += 4;

			}

			m_indexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);

			delete[] indices;
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const math::vec2& size = renderable->getSize();
			const math::vec3& position = renderable->getPosition();
			const math::vec4& color = renderable->getColor();
			const std::vector<math::vec2>& uv = renderable->getUV();
			const GLuint tid = renderable->getTID();

			unsigned int col = 0;
			float ts = 0.0f;

			// check if a txture is going to be rendered, if so map the tecture
			// otherwise set the color.
			if (tid > 0) {
				bool found = false;

				for (int i = 0; i < m_textureSlots.size(); i++) {
					if (m_textureSlots[i] == tid) {
						found = true;
						ts = (float)(i + 1);
						break;
					}
				}

				if (!found) {
					if (m_textureSlots.size() >= MAX_TEXTURE_SLOTS) {
						end();
						flush();
						begin();
					}
					m_textureSlots.push_back(tid);
					ts = (float)(m_textureSlots.size());
				}
			}
			else {
				int r = color.x * 255.0f;
				int g = color.y * 255.0f;
				int b = color.z * 255.0f;
				int a = color.w * 255.0f;

				col = a << 24 | b << 16 | g << 8 | r;
			}

			// m_buffer points to frist element in the buffer
			// write the attributes of the vertex, then increment the m_buffer to the next position.
			m_buffer->vertex = position;
			m_buffer->uv = uv[0];
			m_buffer->tid = ts;
			m_buffer->color = col;
			m_buffer++;

			m_buffer->vertex = math::vec3(position.x, position.y + size.y, position.z);
			m_buffer->uv = uv[1];
			m_buffer->tid = ts;
			m_buffer->color = col;
			m_buffer++;

			m_buffer->vertex = math::vec3(position.x + size.x, position.y + size.y, position.z);
			m_buffer->uv = uv[2];
			m_buffer->tid = ts;
			m_buffer->color = col;
			m_buffer++;

			m_buffer->vertex = math::vec3(position.x + size.x, position.y, position.z);
			m_buffer->uv = uv[3];
			m_buffer->tid = ts;
			m_buffer->color = col;
			m_buffer++;

			m_indexCount += 6;

		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{
			for (int i = 0; i < m_textureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			glBindVertexArray(m_vertexArray);
			m_indexBuffer->bind();

			//glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

			m_indexBuffer->unbind();
			glBindVertexArray(0);

			m_indexCount = 0;
		}

	}
}
