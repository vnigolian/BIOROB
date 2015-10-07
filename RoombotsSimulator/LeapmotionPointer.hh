#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"

#define LEAP_POINTER_SIZE 0.2f
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.005f

class LeapmotionPointer
{
	Leap::Vector _offset;
	Leap::Controller _controller;
	Cube _pointerModel;
	glm::vec3 _position;
	Quad _shadow;
	
public:
	void update();
	void Draw(const glm::mat4& VP) const;
	void Init();
	bool Pinching()const;
	glm::vec3 Position() const;

};