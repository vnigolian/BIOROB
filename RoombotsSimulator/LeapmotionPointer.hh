#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"
#include "Structure.hh"

#define LEAP_POINTER_SIZE 0.2f
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.005f

/* This class represents a pointer controlled with the LeapMotion device.
It allows the user to grab and drag structures only with his/her right-most hand.
Moving the hand will move the LeapmotionPointer and pinching will grab a structure if it is close enough.
*/
class LeapmotionPointer
{
	Leap::Vector _offset; //The offset to convert the Leapmotion coordinate system into the scene's coordinate system
	Leap::Controller _controller; //The Object representing the LeapMotion device
	Cube _pointerModel;//The Model representing the LeapmotionPointer in the scene (for now a cube)
	glm::vec3 _position;//The current position of the LeapmotionPointer
	Structure* _p_structure; //a pointer to the Structure being dragged by the LeapmotionPointer
	
public:
	/*Default constructor that allows to use a LeapmotionPointer*/
	LeapmotionPointer();

	/*Updates the LeapmotionPointer's position and drags the pinched structure if there is one.*/
	void update();

	/*Draws the Model of the LeapmotionPointer*/
	void Draw(const glm::mat4& VP) const;

	bool Pinching()const;
	glm::vec3 Position() const;
	void AssignStructure(Structure* p_structure);
	Structure* AssignedStructure() const;
};