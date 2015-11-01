#include "Model.hh"

Model::Model(){}

void Model::SetModelMatrix(const glm::mat4& M)
{
	this->_M = M;
}


void Model::SetVerticesAndUVs(std::vector<glm::vec3> *vertices, std::vector<glm::vec2> *uvs)
{
	SetVertices(vertices);
	SetUVs(uvs);
	
	while (uvs->size() < vertices->size())
	{
		uvs->push_back(glm::vec2(0.0f, 0.0f));
	}
	while (uvs->size() > vertices->size())
	{
		uvs->pop_back();
	}

}

void Model::SetVertices(std::vector<glm::vec3> *vertices){}
void Model::SetUVs(std::vector<glm::vec2> *uvs){}

void Model::Init(char* vShaderFileName, 
	             char* fShaderFileName, 
				 char* textureFileName)
{
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	SetVerticesAndUVs(&vertices, &uvs);

	_nVertices = vertices.size();
	_nUVs = uvs.size();

	//this loop flips the uvs as SOIL loads the image inverted for some reason...
	for (int i(0); i < _nUVs; i++)
	{
		uvs[i] = (glm::vec2(1.0 - uvs[i].x, uvs[i].y));
	}

	//if there are a different number of vertices than UVs, the OpenGL renderer will crash so we
	//dont let it load the model and simply tell the user the present model can't be loaded
	if (_nVertices != _nUVs)
	{
		std::cerr << "ERROR - INVALID MODEL CLASS DEFINITION \n Every inherited Model class should have as much UV coordinates as vertices\n";
	}
	else
	{
		///--- Compile the shaders
		Core::ShaderLoader shaderLoader;
		_pid = shaderLoader.CreateProgram(vShaderFileName, fShaderFileName);
		
		if (!_pid) exit(EXIT_FAILURE);

		glUseProgram(_pid);

		///--- Vertex one vertex Array
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);


		///--- Vertex coordinates
		{
			///--- Buffer
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, _nVertices * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

			///--- Attribute
			GLuint vpoint_id = glGetAttribLocation(_pid, "vpoint");
			glEnableVertexAttribArray(vpoint_id);
			glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		//Texture coordinates
		{
			//Buffer
			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, _nUVs * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

			//Attribute
			GLuint vtexcoord_id = glGetAttribLocation(_pid, "vtexcoord");
			glEnableVertexAttribArray(vtexcoord_id);
			glVertexAttribPointer(vtexcoord_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		//Load texture
		glGenTextures(1, &_tex);
		glBindTexture(GL_TEXTURE_2D, _tex);

		int width = 0; //IMPORTANT ! HOW THE HELL ARE THOSE USED ?!
		int height = 0;
		unsigned char* image = SOIL_load_image(textureFileName, &width, &height, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		GLuint tex_id = glGetUniformLocation(_pid, "tex");
		glUniform1i(tex_id, GL_TEXTURE0);

		//to terminate the bindings
		glBindVertexArray(0);
		glUseProgram(0);

		_initialized = true;
		_vShader = vShaderFileName;
		_fShader = fShaderFileName;
		_texture = textureFileName;

	}
}

void Model::Init(char* vShaderFileName,
	             char* fShaderFileName,
	             char* textureFileName,
	             glm::vec4& color)
{
	Init(vShaderFileName, fShaderFileName, textureFileName);
	_color = color;
}

void Model::CleanUp() const
{
	if (_initialized)
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
		glDeleteProgram(_pid);
		glDeleteTextures(1, &_tex);
	}
}

void Model::Draw(const glm::mat4& VP) const
{
	if (_initialized)
	{
		glUseProgram(_pid);
		glBindVertexArray(_vao);
		//Activate and bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _tex);

		//setup MVP from the VP passed in argument and the model's model matrix
		glm::mat4 MVP = VP * _M;
		GLuint MVP_id = glGetUniformLocation(_pid, "MVP");
		glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &MVP[0][0]);

		GLuint color_id = glGetUniformLocation(_pid, "colorVec");
		glUniform4f(color_id, _color.x, _color.y, _color.z,_color.w);

		//actual draw
		//glDrawArrays(GL_TRIANGLES, 0, _nVertices);
		glDrawArrays(GL_TRIANGLES, 0, _nVertices);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

void Model::DrawWithLines(const glm::mat4& VP) const
{
	Draw(VP);

	if (_initialized)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0f);
		glUseProgram(_pid);
		glBindVertexArray(_vao);
		//Activate and bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _tex);

		//setup MVP from the VP passed in argument and the model's model matrix
		glm::mat4 MVP = VP * _M;
		GLuint MVP_id = glGetUniformLocation(_pid, "MVP");
		glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &MVP[0][0]);

		GLuint color_id = glGetUniformLocation(_pid, "colorVec");
		glUniform4f(color_id, 0.0f,0.0f,0.0f,1.0f);

		//actual draw
		glDrawArrays(GL_TRIANGLES, 0, _nVertices);
		glBindVertexArray(0);
		glUseProgram(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}

