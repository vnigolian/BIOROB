#pragma once

#include "Button.hh"
#include "LeapmotionPointer.hh"
#include "Structure.hh"

#define BUTTON_SEPARATION 0.1f
#define BUTTON_UP_START 0.1f
#define BUTTON_DEPTH_OFFSET -1.6f
#define BUTTON_LEFT_OFFSET 0.8f

class GUI
{
	std::vector<const Button> buttons;//The models contained in the scene
	size_t nButtons = 0;//The number of models in the scene
	std::vector<const Structure> structures;
	size_t nStructures = 0;

	LeapmotionPointer _pointer;

	void AddButton();
	
	void CheckForPinchedStructure();
	void UpdatePointer();

public:

	GUI();
	void Init();
	void Update();
	void const Render(const glm::mat4& VP);
	size_t NButtons();
	void CleanUp();
};