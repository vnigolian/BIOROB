#include "Cube.hh"

Cube* Cube::copy() const
{
	Cube* p_newCube = NULL;
	Cube newCube;

	if (_initialized)
	{
		newCube.Init(_vShader, _fShader, _texture);
		newCube.SetModelMatrix(_M);
		p_newCube = (Cube*)malloc(sizeof(Cube));
		
		if (p_newCube != NULL)
		{
			*p_newCube = newCube;
		}
	}

	return p_newCube;
}

	void Cube::SetVertices(std::vector<glm::vec3> *vertices)
	{
		typedef glm::vec3 vec3;//just for readability purpose

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

	void Cube::SetUVs(std::vector<glm::vec2> *uvs)
	{
		typedef glm::vec2 vec2;//just for readability purpose
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
