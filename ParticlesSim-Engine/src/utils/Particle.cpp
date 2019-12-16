#include "Particle.h"
#include "../graphics/Window.h"

namespace particlesSimulator {

	particlesSimulator::Particle::Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture)
		: m_mass(mass)
	{
		m_sprite = new graphics::Sprite(x, y, 2 * radius, 2 * radius, texture);
		m_velocity = new math::vec2(xVel, yVel);
	}

	void Particle::updatePosition()
	{
		const math::vec3& oldPos = m_sprite->getPosition();
		float x_new = oldPos.x + m_velocity->x * t_interval;
		float y_new = oldPos.y + m_velocity->y * t_interval;
		
		bool edge = false;
		
		const math::vec2& size = m_sprite->getSize();
		
		if (((x_new + size.x) >= orig_window_width) || (x_new <= (-orig_window_width))) {
			m_velocity->x = -(m_velocity->x);
			edge = true;
		}
		else if (((y_new + size.y ) >= (float)orig_window_height) || (y_new <= (-(float)orig_window_height))) {
			m_velocity->y = -(m_velocity->y);
			edge = true;
		}

		if (edge) {
			x_new = oldPos.x + m_velocity->x * t_interval;
			y_new = oldPos.y + m_velocity->y * t_interval;
			edge = false;
		}


		m_sprite->updateRenderPosition(x_new, y_new);
	}

}
