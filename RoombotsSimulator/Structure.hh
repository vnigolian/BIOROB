#pragma once

#include "Button.hh"

#define MODULE_SIZE 0.1f
#define DRAG_RADIUS 0.2f

class Structure
{
	Cube _model;
	Quad _shadow;

	glm::vec3 _position;
	int _ID;
	Button* _p_button = NULL;

	bool _moving = false;

public:
	Structure(glm::vec3 position, int ID, Button* p_button);
	void Drop();
	void Drag(const glm::vec3& position);
	void Draw(const glm::mat4& VP) const;
	glm::vec3 Position() const;
	bool Moving() const;
};