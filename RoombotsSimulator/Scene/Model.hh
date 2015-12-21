#pragma once

#include "..\common.hh"
#include "..\ShaderLoader.hh"


__declspec(align(16)) class Model{
	GLuint  _vao;          // vertex array object
	GLuint  _pid;          // GLSL shader program ID 
	GLuint  _vbo;          // positions buffer
	GLuint  _tex;          // Texture ID
	GLsizei _nVertices;    // number of vertices
	GLsizei _nUVs;         // number of uvs

public:
	Model(const std::string vShaderFileName,
		const std::string fShaderFileName,
		const std::string textureFileName,
		const glm::vec4& color) : 
		Model(vShaderFileName.c_str(), fShaderFileName.c_str(), textureFileName.c_str(), color){}

	Model(const char* vShaderFileName,
		const char* fShaderFileName,
		const char* textureFileName,
		const glm::vec4& color);

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	const char* Texture(){ return _texture; }  

	virtual Model* copy() const = 0;


	/*Sets the model matrix as the one passed in argument
	  The model matrix defines the scale, rotation and translation of the model
	  It doesn't change its vertices or definition but how and where it will appear 
	  in the scene*/
	void SetModelMatrix(const glm::mat4& M);

	/*Draws the model into the scene.
	  The Projection-View matrix passed in argument is required by the shaders*/
	void Draw(const glm::mat4& VP) const;


	void DrawWithLines(const glm::mat4& VP) const;

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

	glm::mat4 _M = glm::mat4(1.0f);            // model matrix
	GLboolean _initialized= false;     // set on 'true' once initialized
	const char*     _vShader = "";
	const char*     _fShader = "";
	const char*     _texture = "";
	glm::vec4 _color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); //The color of the Model (black by default)

	void SetVerticesAndUVs(std::vector<glm::vec3> *vertices, std::vector<glm::vec2> *uvs);

	/*Defines the vertices of the model.
	  Each series of 3 vertices (each stored as a vec3) will compose a new triangle to be rendered.
	  If the number of vertices isn't a multiple of three, the exceeding vertices will simply be ignored.*/
	virtual void SetVertices(std::vector<glm::vec3> *vertices) = 0;

	/*Defines the texture coordinates (also called 'UVs') of the model
	  UVs are used to make a correspondance between a vertex and a position in the texture
	  in order to determine the color of every vertex and interpolate between them to set the
	  color of every pixel*/
	virtual void SetUVs(std::vector<glm::vec2> *uvs) = 0;

	
	virtual void Init();
};
