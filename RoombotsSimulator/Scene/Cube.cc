#include "Cube.hh"

Cube::Cube(char* vShaderFileName,
	char* fShaderFileName,
	char* textureFileName) : Model(vShaderFileName, fShaderFileName, textureFileName) {}


Cube* Cube::copy() const
{
	return new Cube(_vShader,_fShader,_texture);
}

	void Cube::SetVertices(std::vector<vec3> *vertices)
	{
		vertices->push_back(vec3(-0.5, -0.5, -0.5));
		vertices->push_back(vec3(-0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, -0.5, -0.5));
		vertices->push_back(vec3(-0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, -0.5, -0.5));
		vertices->push_back(vec3(0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, 0.5, 0.5));
		vertices->push_back(vec3(0.5, -0.5, 0.5));
		vertices->push_back(vec3(0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, -0.5, 0.5));
		vertices->push_back(vec3(0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, -0.5, -0.5));
		vertices->push_back(vec3(0.5, 0.5, 0.5));
		vertices->push_back(vec3(-0.5, 0.5, 0.5));
		vertices->push_back(vec3(0.5, -0.5, 0.5));
		vertices->push_back(vec3(-0.5, 0.5, 0.5));
		vertices->push_back(vec3(0.5, -0.5, 0.5));
		vertices->push_back(vec3(-0.5, -0.5, 0.5));
		vertices->push_back(vec3(-0.5, -0.5, 0.5));
		vertices->push_back(vec3(-0.5, -0.5, -0.5));
		vertices->push_back(vec3(0.5, -0.5, 0.5));
		vertices->push_back(vec3(-0.5, -0.5, -0.5));
		vertices->push_back(vec3(0.5, -0.5, 0.5));
		vertices->push_back(vec3(0.5, -0.5, -0.5));
		vertices->push_back(vec3(-0.5, 0.5, -0.5));
		vertices->push_back(vec3(-0.5, -0.5, -0.5));
		vertices->push_back(vec3(-0.5, 0.5, 0.5));
		vertices->push_back(vec3(-0.5, -0.5, -0.5));
		vertices->push_back(vec3(-0.5, 0.5, 0.5));
		vertices->push_back(vec3(-0.5, -0.5, 0.5));
		vertices->push_back(vec3(0.5, 0.5, -0.5));
		vertices->push_back(vec3(-0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, 0.5, 0.5));
		vertices->push_back(vec3(-0.5, 0.5, -0.5));
		vertices->push_back(vec3(0.5, 0.5, 0.5));
		vertices->push_back(vec3(-0.5, 0.5, 0.5));
	}

	void Cube::SetUVs(std::vector<vec2> *uvs)
	{
		uvs->push_back(vec2(0.333, 0.75));
		uvs->push_back(vec2(0.666, 0.75));
		uvs->push_back(vec2(0.333, 0.5));
		uvs->push_back(vec2(0.666, 0.75));
		uvs->push_back(vec2(0.333, 0.5));
		uvs->push_back(vec2(0.666, 0.5));

		uvs->push_back(vec2(0.666, 0.25));
		uvs->push_back(vec2(0.333, 0.25));
		uvs->push_back(vec2(0.666, 0.5));
		uvs->push_back(vec2(0.333, 0.25));
		uvs->push_back(vec2(0.666, 0.5));
		uvs->push_back(vec2(0.333, 0.5));

		uvs->push_back(vec2(0.666, 0.25));
		uvs->push_back(vec2(0.666, 0.0));
		uvs->push_back(vec2(0.333, 0.25));
		uvs->push_back(vec2(0.666, 0.0));
		uvs->push_back(vec2(0.333, 0.25));
		uvs->push_back(vec2(0.333, 0.0));

		uvs->push_back(vec2(0.0, 0.75));
		uvs->push_back(vec2(0.333, 0.75));
		uvs->push_back(vec2(0.0, 0.5));
		uvs->push_back(vec2(0.333, 0.75));
		uvs->push_back(vec2(0.0, 0.5));
		uvs->push_back(vec2(0.333, 0.5));

		uvs->push_back(vec2(0.666, 0.75));
		uvs->push_back(vec2(0.333, 0.75));
		uvs->push_back(vec2(0.666, 1.0));
		uvs->push_back(vec2(0.333, 0.75));
		uvs->push_back(vec2(0.666, 1.0));
		uvs->push_back(vec2(0.333, 1.0));

		uvs->push_back(vec2(0.666, 0.5));
		uvs->push_back(vec2(0.666, 0.75));
		uvs->push_back(vec2(1.0, 0.5));
		uvs->push_back(vec2(0.666, 0.75));
		uvs->push_back(vec2(1.0, 0.5));
		uvs->push_back(vec2(1.0, 0.75));
	}
