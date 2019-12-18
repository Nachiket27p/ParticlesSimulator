#pragma once

#include "../graphics/Sprite.h";
#include "../graphics/Window.h"
#include "../math/Math.h"
#include "../InitializationData.h"

namespace particlesSimulator {

	class Particle {

	public:
		int gridIndex;

	private:
		graphics::Sprite* m_sprite;
		math::vec2* m_velocity;
		float m_mass;

	protected:
		const float t_interval = 1.0f / 60.0f;

	public:
		Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture);

		void updatePosition(std::vector<std::vector<Particle*>>& grid, const int idx, const int& gridRows, const int& gridCols);

		graphics::Sprite* getSprite() { return m_sprite; }

		/*void setGridIndex(int idx) { gridIndex = idx; }*/

	};
}

