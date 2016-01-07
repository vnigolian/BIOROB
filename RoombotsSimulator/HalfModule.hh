#pragma once

#include "OBJModel.hh"
#include "Position.hh"

/**
	A HalfModule is the half of every RoomBot module
*/

class HalfModule
{
private:
	Position       d_position;     ///<The relative coordinates within the Structure
	OBJModel*      d_p_hemisphere1;///<A pointer to a up-oriented hemisphere Model
	OBJModel*      d_p_hemisphere2;///<A pointer to a down-oriented hemisphere Model
	OBJModel*      d_p_circle;     ///<A pointer to a circle model

public:

	/**Creates a new HalfModule
	\arg \c position The position of the new HalfModule
	\arg \c p_h1 A pointer to the first hemi-sphere OBJModel used to draw the HalfModule
	\arg \c p_h2 A pointer to the second hemi-sphere OBJModel used to draw the HalfModule
	\arg \c p_circle A pointer to the circle OBJModel used to draw all six faces of the HalfModule*/
	HalfModule(Position position, 
		       OBJModel* p_h1, 
		       OBJModel* p_h2, 
		       OBJModel* p_circle);
	
	/**Same as the first constructor, but with all three \c int used to create a new Position*/
	HalfModule(int,
		int,
		int,
		OBJModel* p_h1,
		OBJModel* p_h2,
		OBJModel* p_circle);

	/**Draws the two hemispheres and the circle six times in different positions and orientations.*/
	void Draw(const glm::mat4& VP) const;

	/**Returns the relative Position of the halfModule within its Structure*/
	Position GetPosition() const;

	/**Directly sets the position of the Module.
	This should only be used when running the simulation or when the Module is free from any Structure*/
	void SetPosition(const Position& position);

	/**Cleans up the three Models used in the HalfModule*/
	void CleanUp();
};