#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"

#define MODULE_SIZE 0.03f

class Structure
{
	Cube _model;
	Quad _shadow;
	
	glm::vec3 _position;

	bool _moved = false;
	bool _initialized = false;

	public:
		void Drop();
		void Drag(const glm::vec3& position);
		void Draw(const glm::mat4& VP) const;
		void Init(const glm::vec3& initPosition);
		glm::vec3 Position() const;
};