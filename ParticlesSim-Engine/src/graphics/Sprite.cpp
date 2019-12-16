#include "Sprite.h"

namespace particlesSimulator {
	namespace graphics {

		Sprite::Sprite(float x, float y, float width, float height, const math::vec4& color)
			: Renderable2D(math::vec3(x, y, 0), math::vec2(width, height), color)
		{

		}
		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(math::vec3(x, y, 0), math::vec2(width, height), math::vec4(1, 1, 1, 1))
		{
			m_texture = texture;
		}

		void Sprite::updateRenderPosition(float x, float y)
		{
			m_position.x = x;
			m_position.y = y;
		}
	}
}