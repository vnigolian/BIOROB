#pragma once

#include "Button.hh"

class GUI
{
	std::vector<const Button> buttons;//The models contained in the scene
	size_t nButtons;//The number of models in the scene

public:
	void AddButton(const Button sourceButton);
	void const Render(const glm::mat4& VP);
	size_t NButtons();
	void CleanUp();
};