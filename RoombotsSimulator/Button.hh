#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"




class Button
{
	Cube _model;
	glm::vec3 _position;
	int _ID;

	Quad _shadow;

public:
	
#define BUTTON_SIZE 0.15f

	Button(const Button& sourceButton);
	Button(glm::vec3 position, int ID);

	void Draw(const glm::mat4& VP) const;

	void CheckIfClicked(glm::vec3 position, bool pinching);

	void CleanUp() const;

	glm::vec3 Position() const;

private:
	void Click() const;

};
