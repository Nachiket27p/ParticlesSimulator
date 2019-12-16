#pragma once

#include "../graphics/Sprite.h";
#include "../graphics/Window.h"
#include "../math/Math.h"
#include "../InitializationData.h"

namespace particlesSimulator {

	class Particle {

	private:
		graphics::Sprite* m_sprite;
		math::vec2* m_velocity;
		float m_mass;

	protected:
		const float t_interval = 1.0f / 60.0f;

	public:
		Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture);

		void updatePosition();

		graphics::Sprite* getSprite() { return m_sprite; }
	};
}

