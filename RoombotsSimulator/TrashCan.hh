/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once

#include "common.hh"
#include "Scene\Cube.hh"


class TrashCan
{
#define TRASH_CAN_SIZE 2.0f

	Cube*                 d_model;       //the cube model used to represent the trashcan
	const glm::vec3       d_position;    //its position within the scene

public:

	/*Creates a new TrashCan at the position passed by argument*/
	TrashCan(glm::vec3 position);

	/*Draws the TrashCan*/
	void Draw(const glm::mat4& VP) const;

	/*Cleans up the Model representing the TrashCan*/
	void CleanUp() const;

	/*Returns the trashCan's position */
	glm::vec3 Position() const { return d_position; }
};


