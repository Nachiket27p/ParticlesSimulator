#pragma once

#include <cstddef>
#include "Renderer2D.h"
#include "buffers/IndexBuffer.h"

namespace particlesSimulator {
	namespace graphics {

#define RENDERER_MAX_SPRITES 250000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint m_vertexArray;
			GLuint m_vertexBuffer;
			//GLsizei m_indexCount;
			GLuint m_indexCount;
			IndexBuffer* m_indexBuffer;
			VertexData* m_buffer;
			std::vector<GLuint> m_textureSlots;
			
		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin();
			void submit(const Renderable2D* renderable) override;
			void end();
			void flush() override;

		private:
			inline void init();
		};

	}
}