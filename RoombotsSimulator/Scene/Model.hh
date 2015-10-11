#pragma once

#include "..\common.hh"
#include "..\ShaderLoader.hh"


/*__declspec(align(16)) */class Model{
	GLuint  _vao;          // vertex array object
	GLuint  _pid;          // GLSL shader program ID 
	GLuint  _vbo;          // positions buffer
	GLuint  _tex;          // Texture ID
	GLsizei _nVertices;    // number of vertices
	GLsizei _nUVs;         // number of uvs

public:
	char* Texture()  const { return _texture; } 

	virtual Model* copy() const = 0;

	/*Initializes the Model with a vertex shader, a fragment shader and a texture
	  After this method has been called, the model matrix has yet to be set.
	  NOTE : we must be able to set the model matrix separately in order to modify the
	         model after it has been initialized */
	void Init(char* vShaderFileName, 
		      char* fShaderFileName, 
			  char* textureFileName);

	/*Sets the model matrix as the one passed in argument
	  The model matrix defines the scale, rotation and translation of the model
	  It doesn't change its vertices or definition but how and where it will appear 
	  in the scene*/
	void SetModelMatrix(const mat4& M);

	/*Draws the model into the scene.
	  The Projection-View matrix passed in argument is required by the shaders*/
	void Draw(const glm::mat4& VP) const;

	/*Cleans up everything that has been set up during initialization :
		- the VBO
		- the VAO
		- the shading program
		- the texture*/
	void CleanUp() const;

	/*The two following methods are pure virtual as they are used to define
	the shape and texture coordinates of the model that has to be rendered
	and thus have to be defined for every model
	The vectors passed in argument in both methods are created in the 'Init' method
	IMPORTANT : both vectors MUST have the same size as OpenGL makes a correspondance between
	            the elements of those vectors*/
protected:

	mat4      _M;            // model matrix
	GLboolean _initialized= false;     // set on 'true' once initialized
	char*     _vShader;
	char*     _fShader;
	char*     _texture;

	/*Defines the vertices of the model.
	  Each series of 3 vertices (each stored as a vec3) will compose a new triangle to be rendered.
	  If the number of vertices isn't a multiple of three, the exceeding vertices will simply be ignored.*/
	virtual void SetVertices(std::vector<vec3> *vertices) = 0;

	/*Defines the texture coordinates (also called 'UVs') of the model
	  UVs are used to make a correspondance between a vertex and a position in the texture
	  in order to determine the color of every vertex and interpolate between them to set the
	  color of every pixel*/
	virtual void SetUVs(std::vector<vec2> *uvs) = 0;

};
