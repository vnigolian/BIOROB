/**
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once

#include "common.hh"
#include "Cube.hh"
#include "Quad.hh"
#include "Structure.hh"


class Button
{
	Cube*                 d_model;       ///<the cube model used to represent the button
	Quad*                 d_shadow;      ///<a shadow of the cube projected on the floor
	const glm::vec3       d_position;    ///<its position within the scene
	const unsigned int    d_ID;          ///<its unique ID. Used to pop new Structures on the button
	Structure*            d_p_structure; ///<a pointer to the Structure that pops from the button

public:
	
	/**Creates a new button containing the structure passed as argument*/
	Button(glm::vec3 position, 
		   unsigned int ID, 
		   Structure* p_structure);

	/**Draws the button and its shadow*/
	void Draw(const glm::mat4& VP) const;

	/**Cleans up all the models (cube, shadow and the structure's)
	and deletes the pointer to the Structure, meaning it absolutely 
	shouldn't be accessed once this method has been called*/
	void CleanUp() const;

	/**Returns the button's position */
	glm::vec3 Position() const { return d_position; }

	/**Returns the button's ID */
	unsigned int ID() const { return d_ID; }

	/**Returns a pointer to the assigned Structure*/
	Structure* AssignedStructure() const;

};
