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

	public:
		Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture);

		void updatePosition();
		void checkInteractions(std::vector<Particle*>& gridSlot);
		void checkInteraction(std::vector<Particle*>& particles, int currentIdx);
		void checkInteractionMk2(std::vector<Particle*>& particles, int currentIdx);

		graphics::Sprite* getSprite() { return m_sprite; }

		/*void setGridIndex(int idx) { gridIndex = idx; }*/

	};
}

