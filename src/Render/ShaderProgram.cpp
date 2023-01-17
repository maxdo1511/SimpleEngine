#include "ShaderProgram.h"

namespace Render {
	ShaderProgram::ShaderProgram(const std::string vertexShader, const std::string fragmentShader)
	{
		GLuint vertexID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexID))
		{
			std::cerr << "ERROR::SHADER Copile-vertex" << std::endl;
			return;
		}
		GLuint fragmentID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentID))
		{
			std::cerr << "ERROR::SHADER Copile-fragment" << std::endl;
			glDeleteShader(vertexID);
			return;
		}

		id = glCreateProgram();
		glAttachShader(id, vertexID);
		glAttachShader(id, fragmentID);
		glLinkProgram(id);

		GLint success;
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar log[1024];
			glGetShaderInfoLog(id, 1024, nullptr, log);
			std::cerr << "ERROR::SHADER Link-time error:\n" << log << std::endl;
			return;
		}
		else
		{
			is_Compiled = true;
		}

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(id);
	}

	bool ShaderProgram::createShader(const std::string &source, const GLenum type, GLuint& id)
	{
		id = glCreateShader(type);
		const char* code = source.c_str();
		glShaderSource(id, 1, &code, nullptr);
		glCompileShader(id); 

		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar log[1024];
			glGetShaderInfoLog(id, 1024, nullptr, log);
			std::cerr << "ERROR::SHADER Compile-time error:\n" << log << std::endl;
			return false;
		}
		return true;
	}

	void ShaderProgram::use() const
	{
		glUseProgram(id);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(id);
		id = shaderProgram.id;
		is_Compiled = shaderProgram.isCompiled();

		shaderProgram.id = 0;
		shaderProgram.is_Compiled = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		id = shaderProgram.id;
		is_Compiled = shaderProgram.isCompiled();

		shaderProgram.id = 0;
		shaderProgram.is_Compiled = false;
	}
}