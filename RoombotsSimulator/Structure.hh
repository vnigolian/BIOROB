#pragma once

#include "Button.hh"

#define MODULE_SIZE 0.1f //the size of the Model representing the Structure
#define DRAG_RADIUS 0.07f //The minimum distance to grab a Structure

class Structure
{

	glm::vec3 _position;//The Structure's position
	int _ID;//Its ID
	Button* _p_button = NULL;//A pointer to the button from which the Structure was created
	                         //Set to NULL once it has been dropped

	bool _moving = false;//Whether the Structure is moving or not. (used in Drop())

	Cube _model;//The Model representing the Structure (for now a Cube)
	Quad _shadow;//The Model representing its shadow (usefull to know where the Structure will be dropped

public:
	/*Constructor creating a new Structure at the position position, with ID ID and
	linked to the Button pointed by p_button
	The Models are also initialized depending on the position*/
	Structure(glm::vec3 position, int ID, Button* p_button);

	/*Imidiately Drops the Structure where the shadow is drawn
	There is no movement of the Model, it simply "teleports" on the ground*/
	void Drop();

	/*Moves the Structure to the position passed in argument*/
	void Drag(const glm::vec3& position);

	/*Draws the Structure*/
	void Draw(const glm::mat4& VP) const;

	/*Returns the Structure's position*/
	glm::vec3 Position() const;

	/*Cleans up the Models (_model and _shadow)*/
	void CleanUp();
};