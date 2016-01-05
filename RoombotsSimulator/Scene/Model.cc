#include "Model.hh"


Model::Model(const char* vShaderFileName,
	const char* fShaderFileName,
	const char* textureFileName,
	const glm::vec4& color) 
	: d_M(glm::mat4(1.0f)), 
	d_vShaderFilename(vShaderFileName), 
	d_fShaderFilename(fShaderFileName), 
	d_textureFilename(textureFileName), 
	d_color(color) {}

void Model::SetModelMatrix(const glm::mat4& M)
{
	this->d_M = M;
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

void Model::Init()
{
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	SetVerticesAndUVs(&vertices, &uvs);

	d_nVertices = vertices.size();
	d_nUVs = uvs.size();

	//this loop flips the uvs as SOIL loads the image inverted for some reason...
	for (int i(0); i < d_nUVs; i++)
	{
		uvs[i] = (glm::vec2(1.0 - uvs[i].x, uvs[i].y));
	}

	//if there are a different number of vertices than UVs, the OpenGL renderer will crash so we
	//dont let it load the model and simply tell the user the present model can't be loaded
	if (d_nVertices != d_nUVs)
	{
		std::cerr << "ERROR - INVALID MODEL CLASS DEFINITION \n Every inherited Model class should have as much UV coordinates as vertices\n";
	}
	else
	{
		///--- Compile the shaders
		Core::ShaderLoader shaderLoader;
		d_pid = shaderLoader.CreateProgram(d_vShaderFilename, d_fShaderFilename);
		
		if (!d_pid) exit(EXIT_FAILURE);

		glUseProgram(d_pid);

		///--- Vertex one vertex Array
		glGenVertexArrays(1, &d_vao);
		glBindVertexArray(d_vao);


		///--- Vertex coordinates
		{
			///--- Buffer
			glGenBuffers(1, &d_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
			glBufferData(GL_ARRAY_BUFFER, d_nVertices * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

			///--- Attribute
			GLuint vpoint_id = glGetAttribLocation(d_pid, "vpoint");
			glEnableVertexAttribArray(vpoint_id);
			glVertexAttribPointer(vpoint_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		//Texture coordinates
		{
			//Buffer
			glGenBuffers(1, &d_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
			glBufferData(GL_ARRAY_BUFFER, d_nUVs * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

			//Attribute
			GLuint vtexcoord_id = glGetAttribLocation(d_pid, "vtexcoord");
			glEnableVertexAttribArray(vtexcoord_id);
			glVertexAttribPointer(vtexcoord_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		//Load texture
		glGenTextures(1, &d_tex);
		glBindTexture(GL_TEXTURE_2D, d_tex);

		int width = 0; 
		int height = 0;
		unsigned char* image = SOIL_load_image(d_textureFilename, &width, &height, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		GLuint tex_id = glGetUniformLocation(d_pid, "tex");
		glUniform1i(tex_id, GL_TEXTURE0);

		//to terminate the bindings
		glBindVertexArray(0);
		glUseProgram(0);

		d_initialized = true;
	}
}


void Model::CleanUp() const
{
	if (d_initialized)
	{
		glDeleteBuffers(1, &d_vbo);
		glDeleteVertexArrays(1, &d_vao);
		glDeleteProgram(d_pid);
		glDeleteTextures(1, &d_tex);
	}
}

void Model::Draw(const glm::mat4& VP) const
{
	if (d_initialized)
	{
		glUseProgram(d_pid);
		glBindVertexArray(d_vao);
		//Activate and bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, d_tex);

		//setup MVP from the VP passed in argument and the model's model matrix
		glm::mat4 MVP = VP * d_M;
		GLuint MVP_id = glGetUniformLocation(d_pid, "MVP");
		glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &MVP[0][0]);

		GLuint color_id = glGetUniformLocation(d_pid, "colorVec");
		glUniform4f(color_id, d_color.x, d_color.y, d_color.z,d_color.w);

		//actual draw
		//glDrawArrays(GL_TRIANGLES, 0, _nVertices);
		glDrawArrays(GL_TRIANGLES, 0, d_nVertices);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

void Model::DrawWithLines(const glm::mat4& VP) const
{
	//first, normal drawing
	Draw(VP);

	if (d_initialized)
	{
		//here we use 'GL_LINE' to only draw the lines
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0f);
		glUseProgram(d_pid);
		glBindVertexArray(d_vao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, d_tex);

		glm::mat4 MVP = VP * d_M;
		GLuint MVP_id = glGetUniformLocation(d_pid, "MVP");
		glUniformMatrix4fv(MVP_id, 1, GL_FALSE, &MVP[0][0]);

		GLuint color_id = glGetUniformLocation(d_pid, "colorVec");
		glUniform4f(color_id, 0.0f,0.0f,0.0f,1.0f);

		glDrawArrays(GL_TRIANGLES, 0, d_nVertices);
		glBindVertexArray(0);
		glUseProgram(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}

