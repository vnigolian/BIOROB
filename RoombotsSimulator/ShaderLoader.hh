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

		/**reads the file indicated by 'filename' and returns the whole glsl program*/
		std::string ReadShader(const char *filename);

		/**creates a new shader based on the arguments*/
		GLuint CreateShader(GLenum shaderType,
			                std::string source,
			                char* shaderName);

	public:

		/**creates a new program using the two shaders indicated by the names 
		passed in arguments and returns its ID*/
		GLuint CreateProgram(const char* VertexShaderFilename,
			                 const char* FragmentShaderFilename);



		/**Returns the following simple vertex shader : 
			
			#version 330 core
			uniform mat4 MVP;
			in vec3 vpoint;
			in vec2 vtexcoord;
			out vec2 uv;

			void main(){
				gl_Position =  MVP * vec4(vpoint,1.0); 
				uv = vtexcoord;
			}

		It simply applies the MVP matrix to the vertex' position
		*/
		static std::string DefaultVertexShader();


		/**Returns the following simple fragment shader :
			
			#version 330 core
			uniform sampler2D tex;
			in vec2 uv;
			out vec4 color;
			
			void main(){
				color = vec4(1.0,1.0,1.0,1.0);
			}

		It draws the whole model in plain opaque white
		*/
		static std::string DefaultFragmentShader();
	};