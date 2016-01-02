#include "Cube.hh"
 

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
