#pragma once

#include <iostream>
#include <glad/glad.h>

namespace Render {
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string vertexShader, const std::string fragmentShader);

		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		bool isCompiled() const
		{
			return is_Compiled;
		}

		void use() const; 

	private:
		bool createShader(const std::string &source, const GLenum type, GLuint& id);
		bool is_Compiled = false;
		GLuint id = 0;
	};
}