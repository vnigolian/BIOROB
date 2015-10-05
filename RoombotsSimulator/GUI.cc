#include "GUI.hh"

void GUI::AddButton(const Button sourceButton)
{
	buttons.push_back(sourceButton);

	this->nButtons += 1;
	std::cout << "nb of buttons : " << nButtons << std::endl;
}

void const GUI::Render(const glm::mat4& VP)
{
	for (size_t i(0); i < this->nButtons; i++)
	{
		buttons[i].Draw(VP);
	}
}

size_t GUI::NButtons()
{
	return this->nButtons;
}

void GUI::CleanUp()
{
	for (size_t i(0); i < this->nButtons; i++)
	{
		buttons[i].CleanUp();
	}
}