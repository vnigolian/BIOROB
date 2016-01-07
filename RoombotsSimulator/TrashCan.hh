#pragma once

#include "common.hh"
#include "Cube.hh"

/**The TrashCan gives a way to remove MovableStructures from the Scene by dropping inside of it.*/
class TrashCan
{
	Cube*                 d_model;       ///<the cube model used to represent the trashcan
	const glm::vec3       d_position;    ///<its position within the scene

public:

	/**Creates a new TrashCan
	\arg \c position The position of the new TrashCan*/
	TrashCan(glm::vec3 position);

	/**Draws the TrashCan*/
	void Draw(const glm::mat4& VP) const;

	/**Cleans up the Model representing the TrashCan*/
	void CleanUp() const;

	/**Returns the trashCan's position */
	glm::vec3 Position() const { return d_position; }
};


