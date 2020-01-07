#pragma once

#include <GL/glew.h>
#include "../utils/FileUtils.h"
#include "../math/Math.h"


namespace particlesSimulator {
	namespace graphics {

		class Shader
		{
		private:
			GLuint m_shaderID;
			const char* m_vertPath;
			const char* m_fragPath;

		public:			
			/// <summary>
			/// Initializes a new instance of the <see cref="Shader"/> class.
			/// </summary>
			/// <param name="vertPath">The vert path.</param>
			/// <param name="fragPath">The frag path.</param>
			Shader(const char* vertPath, const char* fragPath);
			~Shader();
						
			/// <summary>
			/// Enables the shader.
			/// </summary>
			void enable() const;			

			/// <summary>
			/// Disables the shader.
			/// </summary>
			void disable() const;
			
			/// <summary>
			/// Gets the shader identifier.
			/// </summary>
			/// <returns></returns>
			GLuint getShaderID() const { return m_shaderID; }
			
			/// <summary>
			/// Sets the uniform1i.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			void setUniform1i(const GLchar* name, int value);
			
			/// <summary>
			/// Sets the uniform1fv.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			/// <param name="count">The count.</param>
			void setUniform1fv(const GLchar* name, float* value, GLsizei count);

			/// <summary>
			/// Sets the uniform1iv.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			/// <param name="count">The count.</param>
			void setUniform1iv(const GLchar* name, int* value, GLsizei count);


			/// <summary>
			/// Sets the uniform1f.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="value">The value.</param>
			void setUniform1f(const GLchar* name, float value);

			/// <summary>
			/// Sets the uniform2f.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="vec">The vec.</param>
			void setUniform2f(const GLchar* name, const math::vec2& vec);
			
			/// <summary>
			/// Sets the uniform3f.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="vec">The vec.</param>
			void setUniform3f(const GLchar* name, const math::vec3& vec);
						
			/// <summary>
			/// Sets the uniform4f.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="vec">The vec.</param>
			void setUniform4f(const GLchar* name, const math::vec4& vec);
						
			/// <summary>
			/// Sets the uniform mat4.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <param name="matrix">The matrix.</param>
			void setUniformMat4(const GLchar* name, const math::mat4& matrix);

		private:			
			/// <summary>
			/// Gets the uniform location.
			/// </summary>
			/// <param name="name">The name.</param>
			/// <returns></returns>
			GLint getUniformLocation(const GLchar* name);
			
			/// <summary>
			/// Loads the vertex and fragment shader code from the files provided.
			/// </summary>
			/// <returns></returns>
			GLuint load();
		};

	}
}
