#pragma once

#include "common.hh"
#include "Scene\Cube.hh"

#define LEAP_POINTER_SIZE 0.03f
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.02f

class LeapmotionPointer
{
	Leap::Vector _offset;
	Leap::Controller _controller;
	Cube _pointerModel;
	glm::vec3 _position;
	
public:
	void update();
	void Draw(const glm::mat4& VP) const;
	void Init();
	bool Pinching()const;
	glm::vec3 Position() const;

};