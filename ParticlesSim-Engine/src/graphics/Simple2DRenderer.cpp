#include "Simple2DRenderer.h"

namespace particlesSimulator {
	namespace graphics {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			m_renderQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_renderQueue.empty()) {
				const StaticSprite* sprite = m_renderQueue.front();

				sprite->getVertexArray()->bind();
				sprite->getIndexBuffer()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", math::mat4::translate(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, 0);

				sprite->getIndexBuffer()->unbind();
				sprite->getVertexArray()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}