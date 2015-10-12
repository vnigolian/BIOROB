#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"
#include "Structure.hh"

#define LEAP_POINTER_SIZE 0.19f
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.005f

class LeapmotionPointer
{
	Leap::Vector _offset;//The offset adapting the Leapmotion's coordinate system to the Scene's
	Leap::Controller _controller;//The object allowing us to get data from the Leapmotion device
	glm::vec3 _position;//The position of the LeapmotionPointer
	Structure* _p_structure = NULL;//A pointer to the Structure being dragged 
	                               //(NULL if no Structure is being dragged)
	bool _init = false;//Set to true once initialized

	Cube _pointerModel;//the Model representing the LeapmotionPointer (for now a Cube)
	
public:
	/*Updates the the LeapmotionPointer's position and drags the pinched Structure if there is one*/
	void update();

	/*Draws the LeapmotionPointer's Model */
	void Draw(const glm::mat4& VP) const;

	/*Initializes the LeapmotionPointer
	Its offset, its position (set to (0,0,0)) and its Model*/
	void Init();

	/*returns whether or not the user's rightmost hand is pinching*/
	bool Pinching()const;

	/*Returns the position of the user's rightmost hand 
	or the last captured position if the hand is out of reach*/
	glm::vec3 Position() const;

	/*Returns a pointer to the Structure being dragged
	Used to keep the pointer to grab another Structure while dragging one*/
	void AssignStructure(Structure* p_structure);

	/*Assigns a Structure to the LeapmotionPointer for dragging*/
	Structure* AssignedStructure() const;
};