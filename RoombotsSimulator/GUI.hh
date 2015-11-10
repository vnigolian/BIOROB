#pragma once

#include "Button.hh"
#include "LeapmotionPointer.hh"
#include "Structure.hh"


class GUI
{
#define BUTTON_SEPARATION 0.3f
#define BUTTON_UP_START 4.0f
#define BUTTON_DEPTH_OFFSET -2.0f
#define BUTTON_LEFT_START 2.0f

	std::vector<const Button> _buttons;//The Models contained in the scene
	size_t _nButtons = 0;//The number of Models in the scene
	std::vector<const MovableStructure> _structures;//The Structures contained in the scene
	size_t _nStructures = 0;//The number of Structures in the scene

	LeapmotionPointer _pointer;//The pointer using the Leapmotion device

	bool _init = false;//Set to true once initialized

	/*Adds a button to the interface (max 3 for now)*/
	void AddButton(Structure structure);
	
	/*Checks for every structure if it is being pinched by the LeapmotionPointer*/
	void CheckForPinchedStructure();

	/*Updates the LeapmotionPointer's position depending on the Leapmotion Controller's data*/
	void UpdatePointer(bool mode);

	void PopStructure(unsigned int buttonID);

public:

	/*Initializes the Graphic User Interface by initializing the LeapmotionPointer and adding Buttons*/
	void Init();

	/*Updates the positions of the Structures and the LeapmotionPointer*/
	void Update(bool mode);

	void UpdateWorldMatrix(const glm::mat4& worldMatrix);

	/*Renders (draws) the Buttons, the Structures and the LeapmotionPointer*/
	void const Render(const glm::mat4& VP);

	/*Returns the number of Buttons in the GUI*/
	size_t NButtons();


	void DroppedStructure(unsigned int buttonID);

	void hello(){ std::cout << "hello" << std::endl; }

	/*Cleans up everything*/
	void CleanUp();
};