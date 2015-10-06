#include "GUI.hh"


void GUI::Init()
{
	_pointer.Init();
	AddButton();
	AddButton();
	AddButton();
}

void GUI::AddButton()
{
	//glm::vec3 position = glm::vec3(BUTTON_LEFT_OFFSET, BUTTON_UP_START - (this->nButtons)*(2*BUTTON_SIZE + BUTTON_SEPARATION) , BUTTON_DEPTH_OFFSET);
	glm::vec3 position = glm::vec3(BUTTON_LEFT_OFFSET, BUTTON_UP_START - (this->nButtons)*(1.1f), BUTTON_DEPTH_OFFSET);

	Button newButton(position, this->nButtons);
	buttons.push_back(newButton);
	this->nButtons += 1;
	std::cout << "nb of buttons : " << buttons.size() << std::endl;
}

void const GUI::Render(const glm::mat4& VP)
{
	for (size_t i(0); i < this->nButtons; i++)
	{
		buttons[i].Draw(VP);
	}
	_pointer.Draw(VP);
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

void GUI::UpdatePointer()
{
	_pointer.update();
}