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
	glm::vec3 position = glm::vec3(BUTTON_LEFT_OFFSET, BUTTON_UP_START - (this->nButtons)*(BUTTON_SIZE+BUTTON_SEPARATION), BUTTON_DEPTH_OFFSET);

	Button newButton(position, (int) this->nButtons);
	buttons.push_back(newButton);
	this->nButtons++;
	std::cout << "nb of buttons : " << buttons.size() << std::endl;

	Structure newStructure(position, (int) this->nStructures, &newButton);
	structures.push_back(newStructure);
	this->nStructures++;
}

void const GUI::Render(const glm::mat4& VP)
{
	for (size_t i(0); i < this->nStructures; i++)
	{
		structures[i].Draw(VP);
	}

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

void GUI::CheckForPinchedStructure()
{
	for (size_t i(0); i < this->nStructures; i++)
	{
		if (glm::distance(structures[i].Position(), _pointer.Position()) < DRAG_RADIUS && _pointer.Pinching())
		{
			structures[i].Drag(_pointer.Position());
		}
		else if (structures[i].Moving())
		{
			structures[i].Drop();
		}
	}
}

void GUI::UpdatePointer()
{
	_pointer.update();
	
	for (size_t i(0); i < nButtons; i++)
	{
		buttons[i].CheckIfClicked(_pointer.Position(), _pointer.Pinching());
	}
}

void GUI::Update()
{
	UpdatePointer();
	CheckForPinchedStructure();
}
