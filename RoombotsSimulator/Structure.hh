#pragma once

#include "Button.hh"

#define MODULE_SIZE 0.1f
#define DRAG_RADIUS 0.07f

class Structure
{

	glm::vec3 _position;
	int _ID;
	Button* _p_button = NULL;

	bool _moving = false;

	Cube _model;
	Quad _shadow;

public:
	//Structure(glm::vec3 position, int ID, Button* p_button);
	Structure(glm::vec3 position, int ID, Button* p_button);
	void Drop();
	void Drag(const glm::vec3& position);
	void Draw(const glm::mat4& VP) const;
	glm::vec3 Position() const;
	bool Moving() const;
};