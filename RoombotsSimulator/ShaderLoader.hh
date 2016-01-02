#pragma once

#include "common.hh"

namespace Core
{

	class ShaderLoader
	{
	private:

		/*reads the file indicated by 'filename' and returns the whole glsl program
		*/
		std::string ReadShader(const char *filename);

		/*creates a new shader based on the arguments
		*/
		GLuint CreateShader(GLenum shaderType,
			                std::string source,
			                char* shaderName);

	public:

		ShaderLoader();
		~ShaderLoader();

		/*creates a new program using the two shaders indicated by the names 
		passed in arguments and returns its ID*/
		GLuint CreateProgram(const char* VertexShaderFilename,
			                 const char* FragmentShaderFilename);

	};
}