#pragma once

#include <GL/glew.h>
#include "../math/Math.h"
#include "Renderable2D.h"

namespace particlesSimulator {
	namespace graphics {

		class Renderer2D
		{
		protected:
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
		};

	}
}
