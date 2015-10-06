#pragma once

#include "Button.hh"
#include "LeapmotionPointer.hh"

#define BUTTON_SEPARATION 0.01f
#define BUTTON_UP_START 1.0f
#define BUTTON_DEPTH_OFFSET -2.0f
#define BUTTON_LEFT_OFFSET -1.0f

class GUI
{
	std::vector<const Button> buttons;//The models contained in the scene
	size_t nButtons = 0;//The number of models in the scene
	LeapmotionPointer _pointer;

	void AddButton();

public:
	void Init();
	void const Render(const glm::mat4& VP);
	size_t NButtons();
	void UpdatePointer();
	void CleanUp();
};