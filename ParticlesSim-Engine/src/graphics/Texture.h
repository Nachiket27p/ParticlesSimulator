#pragma once

#include <string>
#include "GL/glew.h"
#include "../utils/stb_image.h"

namespace particlesSimulator {
	namespace graphics {

#define MAX_TEXTURE_SLOTS 32
		class Texture
		{
		private:
			std::string m_filename;
			GLuint m_textureID;
			GLsizei m_width, m_height;
			unsigned char* m_localBuffer;
			int m_BytesPerPixel;

		public:
			Texture(const std::string& filename);
			~Texture();

			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() const { return m_width; }
			inline const unsigned int getHeight() const { return m_height; }
			inline const unsigned int getID() const { return m_textureID; }

		private:
			GLuint load();
			inline void load_image();

		public:
			static void enableBlending() {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
		};

	}
}

