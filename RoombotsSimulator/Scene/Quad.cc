#include "Quad.hh"

Quad* Quad::copy() const
{
	Quad* p_newQuad = NULL;
	Quad newQuad;

	if (_initialized)
	{
		newQuad.Init(_vShader, _fShader, _texture);
		newQuad.SetModelMatrix(_M);
		p_newQuad = (Quad*)malloc(sizeof(Quad));

		if (p_newQuad != NULL)
		{
			*p_newQuad = newQuad;
		}
	}

	return p_newQuad;
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