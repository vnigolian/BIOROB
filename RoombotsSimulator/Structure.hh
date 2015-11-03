#pragma once

#include "Button.hh"
#include "Scene\HalfModule.hh"
#include "Scene\RoomBot.hh"

//#define MODULE_SIZE 0.1f //the size of the Model representing the Structure
#define DRAG_RADIUS 0.07f //The minimum distance to grab a Structure
#define SHADOW_SIZE 0.3f

class Structure
{
	glm::vec3 _position;//The structure's position
	glm::vec3 _centerOffset;//The difference between the Structure's position and its center
	int _ID;//Its ID
	Button* _p_button = NULL;//A pointer to the button from which the Structure was created
	                         //Set to NULL once it has been dropped

	bool _moving = false;//Whether the Structure is moving or not. (used in Drop())

	std::vector<RoomBot> roomBots; //The RoomBot modules of the Structure
	Quad _shadow; //The Structure's shadow. Helps to see where things are

	void SetCenterOffset();

public:
	/*Constructor creating a new Structure with ID 'ID' and linked to the Button pointed by p_button
	The Roombots have still to be set*/
	Structure(glm::vec3 position, int ID, Button* p_button);

	void Init(std::string sourceFilename);

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
	glm::vec3 Position() const;

	/*Returns the Structure's center position which is an average of the roombots' positions*/
	glm::vec3 Structure::CenterPosition() const;

	Button* LinkedButton() const;

	/*Cleans up the RoomBots*/
	void CleanUp();
};