/**
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/

#pragma once

#include "common.hh"


	class ShaderLoader
	{
	private:

		/**reads a glsl program from a file
		\arg \c filename the name of the file containing the glsl program
		\return a \c string containing the whole file or "invalidShader" if the file couln't be read*/
		std::string ReadShader(const char *filename);

		/**creates a new shader
		\arg \c shaderType the type of shader to create
		\arg \c source the \c string containing the shader program
		\arg \c shaderName the name of the shader
		\return the \c GLuint representing the new shader*/
		GLuint CreateShader(GLenum shaderType,
			                std::string source,
			                char* shaderName);

	public:

		/**creates a new program using the two shaders indicated by the names 
		passed in arguments and returns its ID
		\return the \c GLuint representing the new program*/
		GLuint CreateProgram(const char* VertexShaderFilename,
			                 const char* FragmentShaderFilename);



		/**Returns the following simple vertex shader : 
			
			#version 330 core\n
			uniform mat4 MVP;\n
			in vec3 vpoint;\n
			in vec2 vtexcoord;\n
			out vec2 uv;\n

			void main(){\n
				gl_Position =  MVP * vec4(vpoint,1.0);\n 
				uv = vtexcoord;\n
			}\n

		It simply applies the MVP matrix to the vertex' position
		*/
		static std::string DefaultVertexShader();


		/**Returns the following simple fragment shader :
			
			#version 330 core\n
			uniform sampler2D tex;\n
			in vec2 uv;\n
			out vec4 color;\n
			
			void main(){\n
			\t color = vec4(1.0,1.0,1.0,1.0);\n
			}\n

		It draws the whole model in plain opaque white
		*/
		static std::string DefaultFragmentShader();
	};