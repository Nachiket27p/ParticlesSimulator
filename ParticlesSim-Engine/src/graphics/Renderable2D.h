#pragma once

#include "buffers/Buffer.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "../math/Math.h"
#include "Shader.h"

namespace particlesSimulator {
	namespace graphics {

		struct VertexData
		{
			math::vec3 vertex;
			//math::vec4 color;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			math::vec3 m_position;
			math::vec2 m_size;
			math::vec4 m_color;

		public:
			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color)
				: m_position(position), m_size(size), m_color(color)
			{ }

			virtual ~Renderable2D() {}
			

			inline const math::vec3& getPosition() const { return m_position; }
			inline const math::vec2& getSize() const { return m_size; }
			inline const math::vec4& getColor() const { return m_color; }
			
			

		};

	}
}
