#include "Texture.h"

namespace particlesSimulator {
	namespace graphics {

		Texture::Texture(const std::string& filename)
			: m_filename(filename)
		{
			m_textureID = load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(GL_TEXTURE_2D, &m_textureID);
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_textureID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::load()
		{

			load_image();

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);

			if (m_localBuffer) {
				stbi_image_free(m_localBuffer);
			}

			return result;
		}

		inline void Texture::load_image()
		{
			stbi_set_flip_vertically_on_load(1);
			m_localBuffer = stbi_load(m_filename.c_str(), &m_width, &m_height, &m_BytesPerPixel, 4);
		}

		
	}
}