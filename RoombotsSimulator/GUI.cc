#include "GUI.hh"


void GUI::Init()
{
	_pointer.Init();
	AddButton();
	AddButton();
	AddButton();
	_init = true;
}

void GUI::AddButton()
{
	if (nButtons <= 3)//we want max 3 buttons for now
	{
		//we make the position of the buttons vary to get a line of buttons
		glm::vec3 position = glm::vec3(BUTTON_LEFT_OFFSET, BUTTON_UP_START - (this->nButtons)*(BUTTON_SIZE + BUTTON_SEPARATION), BUTTON_DEPTH_OFFSET);

		//we create the new Button with the position
		Button newButton(position, (int) this->nButtons);
		buttons.push_back(newButton);
		this->nButtons++;

		//and add a structure linked to this button at the same position
		Structure newStructure(position, (int) this->nStructures, &newButton);
		structures.push_back(newStructure);
		this->nStructures++;
	}
}

void const GUI::Render(const glm::mat4& VP)
{
	if (_init)
	{
		//we draw all the structures
		for (size_t i(0); i < this->nStructures; i++)
		{
			structures[i].Draw(VP);
		}

		//all the buttons
		for (size_t i(0); i < this->nButtons; i++)
		{
			buttons[i].Draw(VP);
		}
		//and finally the LeapmotionPointer
		_pointer.Draw(VP);
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
	for (size_t i(0); i < this->nStructures; i++)
	{
		structures[i].CleanUp();
	}
}

void GUI::CheckForPinchedStructure()
{
	for (size_t i(0); i < this->nStructures; i++)
	{
		if (glm::distance(structures[i].Position(), _pointer.Position()) < DRAG_RADIUS && _pointer.Pinching())
		{
			_pointer.AssignStructure(&(structures[i]));
		}
	}
}

void GUI::UpdatePointer()
{
	_pointer.update();
}

void GUI::Update()
{
	if (_init)
	{
		UpdatePointer();
		CheckForPinchedStructure();
	}
}
