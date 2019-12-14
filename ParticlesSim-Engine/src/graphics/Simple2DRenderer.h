#pragma once

#include <deque>
#include "Renderer2D.h"
#include "StaticSprite.h"

namespace particlesSimulator {
	namespace graphics {

		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_renderQueue;
		public:
			virtual void submit(const Renderable2D* renderable) override;
			virtual void flush() override;
		};

	}
}
