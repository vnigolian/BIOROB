#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Structure.hh"


#define BUTTON_SIZE 0.15f
#define BUTTON_RADIUS 0.3f

class Button
{
	Cube _model;
	glm::vec3 _position;
	int _ID;

	Structure _structure;

	Quad _shadow;

public:
	Button(const Button& sourceButton);
	
	Button(vec3 position, int ID);

	void Draw(const glm::mat4& VP) const;

	void CheckIfClicked(glm::vec3 position, bool pinching);

	void CleanUp() const;

private:
	void Click() const;

};