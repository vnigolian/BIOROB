#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"


#define BUTTON_SIZE 0.15f

class Button
{
	Cube _model;
	glm::vec3 _position;
	int _ID;

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