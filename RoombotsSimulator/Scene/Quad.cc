#include "Quad.hh"

Quad* Quad::copy() const
{
	Quad* p_newQuad = new Quad(_vShader, _fShader, _texture, _color);
	p_newQuad->SetModelMatrix(_M);
	return p_newQuad;
}


void Quad::SetVertices(std::vector<glm::vec3> *vertices)
{
vertices->push_back(glm::vec3(-0.5f, 0.0f, -0.5f));
vertices->push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
vertices->push_back(glm::vec3(0.5f, 0.0f, -0.5f));

vertices->push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
vertices->push_back(glm::vec3(0.5f, 0.0f, -0.5f));
vertices->push_back(glm::vec3(0.5f, 0.0f, 0.5f));
}

void Quad::SetUVs(std::vector<glm::vec2> *uvs)
{
	uvs->push_back(glm::vec2(0.0f, 0.0f));
	uvs->push_back(glm::vec2(0.0f, 1.0f));
	uvs->push_back(glm::vec2(1.0f, 0.0f));

	uvs->push_back(glm::vec2(0.0f, 1.0f));
	uvs->push_back(glm::vec2(1.0f, 0.0f));
	uvs->push_back(glm::vec2(1.0f, 1.0f));
}