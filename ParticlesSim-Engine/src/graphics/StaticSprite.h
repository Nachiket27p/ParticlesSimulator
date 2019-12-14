#pragma once

#include "Renderable2D.h"

namespace particlesSimulator {
	namespace graphics {

		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray* m_vertexArray;
			IndexBuffer* m_indexBuffer;
			Shader& m_shader;

		public:
			StaticSprite(float x, float y, float width, float height, const math::vec4& color, Shader& shader);
			~StaticSprite();


			inline Shader& getShader() const { return m_shader; }
			inline const VertexArray* getVertexArray() const { return m_vertexArray; }
			inline const IndexBuffer* getIndexBuffer() const { return m_indexBuffer; }
		};

	}
}
