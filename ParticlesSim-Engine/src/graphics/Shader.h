#pragma once

#include <GL/glew.h>
#include "../utils/FileUtils.h"
#include "../math/Math.h"


namespace particlesSimulator { namespace graphics {

	class Shader
	{
	private:
		GLuint m_shaderID;
		const char* m_vertPath;
		const char* m_fragPath;

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		void disable() const;

		GLuint getShaderID() const { return m_shaderID; }

		void setUniform1i(const GLchar* name, int value);
		void setUniform1f(const GLchar* name, float value);
		void setUniform2f(const GLchar* name, const math::vec2& vec);
		void setUniform3f(const GLchar* name, const math::vec3& vec);
		void setUniform4f(const GLchar* name, const math::vec4& vec);
		void setUniformMat4(const GLchar* name, const math::mat4& matrix);

	private:
		GLint getUniformLocation(const GLchar* name);
		GLuint load();
	};

}}
