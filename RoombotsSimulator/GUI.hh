#pragma once

#include "Button.hh"
#include "LeapmotionPointer.hh"
#include "Structure.hh"
#include "Position.hh"


class GUI
{
#define BUTTON_SEPARATION 1.0f
#define BUTTON_UP_START 1.8f
#define BUTTON_DEPTH_OFFSET -4.5f
#define BUTTON_LEFT_START 2.0f

	std::vector<const Button> _buttons;//The Buttons contained in the scene
	size_t _nButtons = 0;//The number of Buttons in the scene
	std::vector<const MovableStructure> _structures;//The Structures contained in the scene
	size_t _nStructures = 0;//The number of Structures in the scene

	LeapmotionPointer _pointer;//The pointer using the Leapmotion device

	bool _init = false;//Set to true once initialized

	/*Adds a button to the interface (max 3 for now)*/
	void AddButton(Structure* p_structure);
	
	/*Checks for every structure if it is being pinched by the LeapmotionPointer*/
	void CheckForPinchedStructure(); 

	/*Updates the LeapmotionPointer's position depending on the Leapmotion Controller's data*/
	void UpdatePointer(bool mode);

	/*Pops a new structure in the Button whose ID is passed in argument*/
	void PopStructure(unsigned int buttonID);

public:

	/*Initializes the Graphic User Interface by initializing the LeapmotionPointer and adding Buttons*/
	void Init();

	/*Updates the positions of the Structures and the LeapmotionPointer*/
	void Update(bool mode);

	/*Updates the scene's world matrix. 
	  Used to change the behaviour of the LeapmotionPointer depending on the current mode*/
	void UpdateWorldMatrix(const glm::mat4& worldMatrix);

	/*Renders (draws) the Buttons, the Structures and the LeapmotionPointer*/
	void const Render(const glm::mat4& VP);

	/*Returns the number of Buttons in the GUI*/
	size_t NButtons();

	/*Notifies the GUI a Structure has been dropped and pops a new one 
	  on the corresponding button if the ID passed in argument is valid*/
	void DroppedStructure(unsigned int buttonID);

	/*Returns a vector of the positions of all the Roombots*/
	std::vector<Position> GetAllRoombotsPositions();

	/*Cleans up everything*/
	void CleanUp();
};