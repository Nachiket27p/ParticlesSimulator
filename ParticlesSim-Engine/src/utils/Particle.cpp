#include "Particle.h"
#include "../graphics/Window.h"
#include "../InitializationData.h"

namespace particlesSimulator {

	particlesSimulator::Particle::Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture)
		: m_mass(mass)
	{
		m_sprite = new graphics::Sprite(x, y, 2 * radius, 2 * radius, texture);
		m_velocity = new math::vec2(xVel, yVel);
	}

	void Particle::updatePosition()
	{
		const math::vec3& p1Pos = m_sprite->getPosition();

		float x_new = p1Pos.x + m_velocity->x * t_interval;
		float y_new = p1Pos.y + m_velocity->y * t_interval;

		bool edge = false;

		const math::vec2& size = m_sprite->getSize();

		if (((x_new + size.x) >= orig_window_width) || (x_new <= 0)) {
			m_velocity->x = -(m_velocity->x);
			edge = true;
		}
		else if (((y_new + size.y) >= (float)orig_window_height) || (y_new <= 0)) {
			m_velocity->y = -(m_velocity->y);
			edge = true;
		}

		if (edge) {
			x_new = p1Pos.x + m_velocity->x * t_interval;
			y_new = p1Pos.y + m_velocity->y * t_interval;
			edge = false;
		}

		m_sprite->updateRenderPosition(x_new, y_new);

	}

	void Particle::checkInteractions(std::vector<Particle*>& gridSlot)
	{
		bool interaction = false;
		const math::vec3& p1Pos = m_sprite->getPosition();

		// find particles interacting with this one
		float separation = 0.0f;

		float dx, dy, v1x_new, v2x_new, v1y_new, v2y_new, innerProd, reducedMass1, reducedMass2, scalarFactor1, scalarFactor2;
		for (int i = 0; i < gridSlot.size(); i++) {
			const Particle* p2 = gridSlot[i];
			if (this == p2) {
				continue;
			}
			
			const math::vec3& p2Pos = p2->m_sprite->m_position;
			dx = p1Pos.x - p2Pos.x;
			dy = p1Pos.y - p2Pos.y;
			
			separation = dx*dx + dy*dy; // Also the norm of the position vector from particle 1 to particle 2

			//if (abs(dx) <= particle0_diameter && abs(dy) <= particle0_diameter) {
			if (separation <= particle0_diameter_Sqrd) {
				interaction = true;

				innerProd = ((m_velocity->x - p2->m_velocity->x) * (p1Pos.x - p2Pos.x)) + ((m_velocity->y - p2->m_velocity->y) * (p1Pos.y - p2Pos.y));
				//norm = separation;

				reducedMass1 = ((2 * p2->m_mass) / (m_mass + p2->m_mass));
				reducedMass2 = ((2 * m_mass) / (m_mass + p2->m_mass));

				scalarFactor1 = (reducedMass1 * (innerProd / separation));
				scalarFactor2 = (reducedMass2 * (innerProd / separation));

				v1x_new = m_velocity->x - (scalarFactor1 * dx);
				v1y_new = m_velocity->y - (scalarFactor1 * dy);

				v2x_new = p2->m_velocity->x - (scalarFactor2 * (-dx));
				v2y_new = p2->m_velocity->y - (scalarFactor2 * (-dy));

				m_velocity->x = v1x_new;
				m_velocity->y = v1y_new;

				p2->m_velocity->x = v2x_new;
				p2->m_velocity->y = v2y_new;

			}
		}
	}
}
