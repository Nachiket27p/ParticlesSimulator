#pragma once

#include "../graphics/Sprite.h";
#include "../graphics/Window.h"
#include "../math/Math.h"
#include "../InitializationData.h"

/// <summary>
/// Responsible for creating a particle object which holds a sprite object which is given to the renderer.
/// Keeps track of the particles velocity velocity.
/// </summary>
namespace particlesSimulator {

	class Particle {
	private:
		graphics::Sprite* m_sprite;
		math::vec2* m_velocity;
		float m_mass;

	public:
		/// <summary>
		/// Particles the specified x.
		/// </summary>
		/// <param name="x">The x position the particle.</param>
		/// <param name="y">The y position of the particle.</param>
		/// <param name="xVel">The velocity in the x direction.</param>
		/// <param name="yVel">The velocity in the y direction.</param>
		/// <param name="radius">The radius.</param>
		/// <param name="mass">The mass.</param>
		/// <param name="texture">The texture.</param>
		/// <returns></returns>
		Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture);
		
		
		void updatePosition();
		
		/// <summary>
		/// Checks the interactions.
		/// </summary>
		/// <param name="gridSlot">The grid slot.</param>
		void checkInteractions(std::vector<Particle*>& gridSlot);

		// TOO GLITCHY: particles keep overlapping due to multiple interactions occuring within small timeframe.
		/// <summary>
		/// Checks the interaction.
		/// </summary>
		/// <param name="particles">The particles.</param>
		/// <param name="currentIdx">Index of the current.</param>
		void checkInteraction(std::vector<Particle*>& particles, int currentIdx);

		/// <summary>
		/// Checks the interaction MK2.
		/// </summary>
		/// <param name="particles">The particles.</param>
		/// <param name="currentIdx">Index of the current.</param>
		void checkInteractionMk2(std::vector<Particle*>& particles, int currentIdx);

		graphics::Sprite* getSprite() { return m_sprite; }

		/*void setGridIndex(int idx) { gridIndex = idx; }*/

	};
}

