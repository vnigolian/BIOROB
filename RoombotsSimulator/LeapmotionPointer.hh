#pragma once

#include "common.hh"
#include "Scene\Cube.hh"
#include "Scene\Quad.hh"
#include "MovableStructure.hh"

class GUI;

class LeapmotionPointer
{
#define LEAP_POINTER_SIZE 1.0f
#define COORDINATE_SYSTEM_SCALE_CONVERSION 0.005f
#define BOX_COORDINATE_SYSTEM_SCALE_CONVERSION 0.016f
#define PINCHING_LIMIT 0.7f

	Leap::Controller  d_controller;                       //The object allowing us to get data from the Leapmotion device
	glm::vec3         d_position;                         //The position of the LeapmotionPointer
	MovableStructure* d_p_structure = NULL;               //A pointer to the Structure being dragged 
	                                                      //(NULL if no Structure is being dragged)
	glm::mat4         d_invertedWorldMatrix = glm::mat4();//This matrix is the inverse from the Scene's WorldMatrix.
	                                                      //It allows the user to move around in the room and move 
	                                                      //Structures more easily
	bool              d_init = false;                     //Set to true once initialized
	Cube*             d_p_pointerModel;                   //the Cube representing the LeapmotionPointer and 
	                                                      //changing size depending on its pinching value
	Cube*             d_p_referencePointerModel;          //the reference Cube that doesn't change size
	Quad*             d_p_shadow;                         //the Quad projected on the floor, helping perceive depth
	GUI*              d_p_gui;                            //A pointer to the GUI so it can tell it to add a new Structure 
	                                                      //to a button once it's dropped


	
public:

	/*Initializes the LeapmotionPointer
	Its offset, its position (set to (0,0,0)) and its Model*/
	void Init(GUI* p_gui);

	/*Updates the the LeapmotionPointer's position and drags the pinched Structure if there is one*/
	void update(bool mode);

	/*Updates the _invertedWorldMatrix with the one from the main*/
	void UpdateWorldMatrix(const glm::mat4& worldMatrix);

	/*Draws the LeapmotionPointer's Model */
	void Draw(const glm::mat4& VP) const;


	/*returns whether or not the user's rightmost hand is pinching*/
	bool Pinching()const;

	/*Returns the position of the user's rightmost hand 
	or the last captured position if the hand is out of reach*/
	glm::vec3 Position() const;

	/*Returns a pointer to the Structure being dragged
	Used to keep the pointer to grab another Structure while dragging one*/
	void AssignStructure(MovableStructure* p_structure);

	/*Assigns a Structure to the LeapmotionPointer for dragging*/
	MovableStructure* AssignedStructure() const;

	void CleanUp();

private:
	/*Adapts the offset, the limits and the sensitivity of the pointer depending on the current mode*/
	Leap::Vector adaptToMode(Leap::Vector right_hand_pos, bool mode);
};