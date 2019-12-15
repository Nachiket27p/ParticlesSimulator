#include <vector>
#include "Shader.h"
#include "IOHandler.h"

namespace particlesSimulator {
	namespace graphics {

		Shader::Shader(const char* vertPath, const char* fragPath)
			:m_shaderID(0), m_vertPath(vertPath), m_fragPath(fragPath)
		{
			m_shaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		void Shader::enable() const
		{
			glUseProgram(m_shaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform1fv(const GLchar* name, float* value, GLsizei count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1iv(const GLchar* name, int* value, GLsizei count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar* name, const math::vec2& vec)
		{
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}

		void Shader::setUniform3f(const GLchar* name, const math::vec3& vec)
		{
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
		}

		void Shader::setUniform4f(const GLchar* name, const math::vec4& vec)
		{
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const math::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_shaderID, name);
		}

		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();

			// vertex shader
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

			std::string vertss = FileUtils::read_file(m_vertPath);
			const char* vertexSource = vertss.c_str();

			glShaderSource(vertex, 1, &vertexSource, NULL);
			glCompileShader(vertex);

			GLint vResult;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &vResult);
			if (vResult == GL_FALSE) {
				GLint len;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &len);
				std::vector<char> error(len);
				glGetShaderInfoLog(vertex, len, &len, &error[0]);
				PRINT_ERROR("Failed to compile vertex shader!", &error[0]);
				glDeleteShader(vertex);
				return 0;
			}

			// fragment shader
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string fragss = FileUtils::read_file(m_fragPath);
			const char* fragmentSource = fragss.c_str();

			glShaderSource(fragment, 1, &fragmentSource, NULL);
			glCompileShader(fragment);

			GLint fResult;
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &fResult);
			if (fResult == GL_FALSE) {
				GLint len;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &len);
				std::vector<char> error(len);
				glGetShaderInfoLog(fragment, len, &len, &error[0]);
				PRINT_ERROR("Failed to compile fragment shader!", &error[0]);
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

	}
}
