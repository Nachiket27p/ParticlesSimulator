#pragma once

#include <unordered_map>
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
		std::unordered_map<const Particle*, bool> interactedWith;

	public:
		
		/**
		 * @brief Constructor for particle.
		 * @param x The x position the particle.
		 * @param y The y position of the particle.
		 * @param xVel The velocity in the x direction.
		 * @param yVel The velocity in the y direction.
		 * @param radius The radius.
		 * @param mass The texture.
		 * @param texture 
		*/
		Particle(float x, float y, float xVel, float yVel, float radius, float mass, graphics::Texture* texture);
		
		
		void updatePosition();
		
		/**
		 * @brief Checks the interactions.
		 * @param gridSlot The grid slot.
		*/
		void checkInteractions(std::vector<Particle*>& gridSlot);

		/**
		 * @brief Checks the interactions.
		 * @param gridSlot The grid slot.
		 * @param particlesOnEdge The associate list of particles which are overlapping into the gridSlot provided.
		*/
		void checkInteractions(std::vector<Particle*>& gridSlot, std::vector<Particle*>& particlesOnEdge);

		/**
		 * @brief Checks the interaction. TOO GLITCHY: particles keep overlapping due to multiple interactions
		 * occuring within small timeframe.
		 * @param particles The particles.
		 * @param currentIdx Index of the current.
		*/
		void checkInteraction(std::vector<Particle*>& particles, int currentIdx);
		
		/**
		 * @brief Checks the interaction MK2.
		 * @param particles The particles.
		 * @param currentIdx Index of the current.
		*/
		void checkInteractionMk2(std::vector<Particle*>& particles, int currentIdx);

		/**
		 * @brief Adds the pointer to the list of particles this particle has interacted with.
		 * @param otherParticle Pointer to the other particle.
		*/
		void addInteractedWith(Particle* otherParticle);

		/**
		 * @brief Check if the particle provided has interacted with this one.
		 * @param otherParticle Pointer to other particle.
		 * @return true if this particle has interacted with 'otherParticle', otherwise false.
		*/
		inline const bool hasInteractedWith(Particle* otherParticle);

		/**
		 * @brief Clears the list of interacted particles
		*/
		void resetInteractedWith();

		/**
		 * @brief Returns the spriate representation of this particle.
		 * @return Sprite object associated with this particle.
		*/
		graphics::Sprite* getSprite() { return m_sprite; }

		/*void setGridIndex(int idx) { gridIndex = idx; }*/

	};
}
