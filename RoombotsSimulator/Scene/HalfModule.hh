#pragma once

#include "OBJModel.hh"
#include "../Position.hh"


class HalfModule
{
private:
	Position _position;//The relative coordinates within the Structure

	OBJModel* _hemisphere1;//A pointer to a up-oriented hemisphere Model
	OBJModel* _hemisphere2;//A pointer to a down-oriented hemisphere Model
	OBJModel* _circle;//A pointer to a circle model

public:

	HalfModule(int, int, int, OBJModel* p_h1, OBJModel* p_h2);
	HalfModule(Position position, OBJModel* p_h1, OBJModel* p_h2);

	/*Draws the two hemispheres and the circle six times in different positions and orientations.*/
	void Draw(const glm::mat4& VP) const;

	/*Returns the relative Position of the halfModule within its Structure*/
	Position getPosition() const;

	/*Directly sets the position of the Module.
	This should only be used when running the simulation or when the Module is free from any Structure*/
	void setPosition(const Position& position);

};