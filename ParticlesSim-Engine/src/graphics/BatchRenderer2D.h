#pragma once

#include <cstddef>
#include "Renderer2D.h"
#include "buffers/IndexBuffer.h"

namespace particlesSimulator {
	namespace graphics {

		// maximum number of sprites the batch renderer can render at once.
#define RENDERER_MAX_SPRITES 250000
		// the size of the vertex
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
		// the size of the sprite being rendered
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
		// the size of the buffer which will hold all the sprites
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
		// the size of the index array used to render the sprites.
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

		// define the indices at which the data will be received in the fragment shader.
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
			/// <summary>
			/// Initializes a new instance of the <see cref="BatchRenderer2D"/> class.
			/// </summary>
			BatchRenderer2D();
			~BatchRenderer2D();
			
			/// <summary>
			/// Begins the batch renderer by binding the buffer.
			/// </summary>
			void begin();
			
			/// <summary>
			/// Submits the data in the buffer to be rendered.
			/// </summary>
			/// <param name="renderable">The renderable.</param>
			void submit(const Renderable2D* renderable) override;
			
			/// <summary>
			/// End the batch renderer by unbinding the buffer.
			/// </summary>
			void end();
			
			/// <summary>
			/// Flushes this data from the buffer to the gpu.
			/// </summary>
			void flush() override;

		private:			
			/// <summary>
			/// Initializes this instance.
			/// </summary>
			inline void init();
		};

	}
}