#pragma once

#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "../math/Math.h"
#include "Shader.h"
#include "Texture.h"


namespace particlesSimulator {
	namespace graphics {

		struct VertexData
		{
			math::vec3 vertex;
			math::vec2 uv;
			float tid;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			math::vec3 m_position;
			math::vec2 m_size;
			math::vec4 m_color;
			std::vector<math::vec2> m_uv;
			Texture* m_texture;

		public:

			Renderable2D() { setUVDefaults(); }

			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color)
				: m_position(position), m_size(size), m_color(color)
			{
				setUVDefaults();
			}

			virtual ~Renderable2D() {}
			

			inline const math::vec3& getPosition() const { return m_position; }
			inline const math::vec2& getSize() const { return m_size; }
			inline const math::vec4& getColor() const { return m_color; }
			inline const std::vector<math::vec2>& getUV() const { return m_uv; }

			inline const GLuint getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }

		private:
			void setUVDefaults()
			{
				m_uv.push_back(math::vec2(0, 0));
				m_uv.push_back(math::vec2(0, 1));
				m_uv.push_back(math::vec2(1, 1));
				m_uv.push_back(math::vec2(1, 0));
			}
			

		};

	}
}
