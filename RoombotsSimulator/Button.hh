#pragma once

#include "common.hh"

#define BUTTON_RADIUS 0.3f

class Button
{
	glm::vec3 _position;

public:
	void Init();

	void Draw() const;



};