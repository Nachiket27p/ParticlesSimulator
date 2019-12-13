#include "Simple2DRenderer.h"

namespace particlesSimulator {
	namespace graphics {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			m_renderQueue.push_back(renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_renderQueue.empty()) {
				const Renderable2D* renderable = m_renderQueue.front();

				renderable->getVertexArray()->bind();
				renderable->getIndexBuffer()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", math::mat4::translate(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, 0);

				renderable->getIndexBuffer()->unbind();
				renderable->getVertexArray()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}