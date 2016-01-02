#pragma once

#include "Button.hh"
#include "Structure.hh"

/**
	This class encapsulates a Roombot Structure as something that interact with the buttons
	and the LeapmotionPointer.
	Indeed, Structures are static sets of Roombots Module and are not meant to be moved around.

	This encapsulation allows to use the same Structure for all similar MovableStructures.
	For instance, all 'chairs' MovableStructures use the same Structure through a pointer.

	All the visible Structures when running the software are actually MovableStructures.
*/
class MovableStructure
{
	Structure* const _p_structure; //The pointer to the Structure to be moved
	Position _position;//The structure's position
	int _ID;//Its ID
	unsigned int _buttonID;//The ID of the button from which the Structure was created
	                       //Once dropped, it is set to -1 to "unlink" it from the button

	bool _moving = false;//Whether the Structure is moving or not. (used in Drop())

	/*Computes the center's offset from the lower left corner*/
	void SetCenterOffset();

	void setPosition(glm::vec3 position);

public:

	#define DRAG_RADIUS 0.4f //The minimum distance to grab a Structure

	MovableStructure(Structure* p_structure, glm::vec3 position, int ID, unsigned int buttonID);


	/*Returns true if the position passed in argument is close enough from the Structure's center*/
	bool CloseEnough(glm::vec3 position);

	/*Imidiately Drops the Structure where the shadow is drawn
	There is no movement of the Model, it simply "teleports" on the ground*/
	void Drop();

	/*Moves the Structure to the position passed in argument*/
	void Drag(const glm::vec3& position);

	/*Draws the Structure*/
	void Draw(const glm::mat4& VP) const;

	/*Returns the reference position of the Structure*/
	Position getPosition() const;

	/*Returns the ID of the button from which the MovableStructure comes*/
	unsigned int LinkedButtonID() const;

	/*Returns the positions of all the Roombots of its Structure*/
	std::vector<Position> RoombotsPositions() const;
};