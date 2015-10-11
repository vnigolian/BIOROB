#include "Quad.hh"

Quad::Quad(char* vShaderFileName,
	char* fShaderFileName,
	char* textureFileName) : Model(vShaderFileName, fShaderFileName, textureFileName) {}


Quad* Quad::copy() const
{
	return new Quad(_vShader, _fShader, _texture);
}


void Quad::SetVertices(std::vector<vec3> *vertices)
{
vertices->push_back(vec3(-0.5f, 0.0f, -0.5f));
vertices->push_back(vec3(-0.5f, 0.0f, 0.5f));
vertices->push_back(vec3(0.5f, 0.0f, -0.5f));

vertices->push_back(vec3(-0.5f, 0.0f, 0.5f));
vertices->push_back(vec3(0.5f, 0.0f, -0.5f));
vertices->push_back(vec3(0.5f, 0.0f, 0.5f));
}

void Quad::SetUVs(std::vector<vec2> *uvs)
{
	uvs->push_back(vec2(0.0f, 0.0f));
	uvs->push_back(vec2(0.0f, 1.0f));
	uvs->push_back(vec2(1.0f, 0.0f));

	uvs->push_back(vec2(0.0f, 1.0f));
	uvs->push_back(vec2(1.0f, 0.0f));
	uvs->push_back(vec2(1.0f, 1.0f));
}