#pragma once

#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "../math/Math.h"
#include "Shader.h"

namespace particlesSimulator {
	namespace graphics {

		class Renderable2D
		{
		protected:
			math::vec3 m_position;
			math::vec2 m_size;
			math::vec4 m_color;

			VertexArray* m_vertexArray;
			IndexBuffer* m_indexBuffer;
			Shader& m_shader;

		public:
			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color, Shader& shader)
				: m_position(position), m_size(size), m_color(color), m_shader(shader)
			{
				m_vertexArray = new VertexArray();

				GLfloat vertices[] =
				{
					0,	0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};
				GLfloat colors[] =
				{//		R		G			B		A
					color[0], color[1], color[2], color[3],
					color[0], color[1], color[2], color[3],
					color[0], color[1], color[2], color[3],
					color[0], color[1], color[2], color[3]
				};

				m_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

				m_indexBuffer = new IndexBuffer(indices, 6);
			}

			~Renderable2D()
			{
				delete m_vertexArray;
				delete m_indexBuffer;
			}

			inline const math::vec3& getPosition() const { return m_position; }
			inline const math::vec2& getSize() const { return m_size; }
			inline const math::vec4& getColor() const { return m_color; }
			
			inline Shader& getShader() const { return m_shader; }

			inline const VertexArray* getVertexArray() const { return m_vertexArray; }
			inline const IndexBuffer* getIndexBuffer() const { return m_indexBuffer; }

		};

	}
}
