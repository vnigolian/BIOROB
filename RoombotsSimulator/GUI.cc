#include "GUI.hh"


void GUI::Init()
{
	_pointer.Init(this);
	Structure newStructure("");

	AddButton(newStructure);
	std::cout << "GUI initialized" << std::endl;
	_init = true;
}

void GUI::AddButton(Structure structure)
{
	if (nButtons <= 3)//we want max 3 buttons for now
	{
		//we make the position of the buttons vary to get a line of buttons
		glm::vec3 position = glm::vec3(BUTTON_LEFT_OFFSET, BUTTON_UP_START - (this->nButtons)*(BUTTON_SIZE + BUTTON_SEPARATION), BUTTON_DEPTH_OFFSET);

		//we create the new Button with the position
		Button newButton(position, (int) this->nButtons,structure);
		buttons.push_back(newButton);
		this->nButtons++;
		//MovableStructure::MovableStructure(Structure structure, glm::vec3 position, int ID, Button* p_button) :

		//and add a structure linked to this button at the same position
		PopStructure(newButton.ID());
	}
}
//MovableStructure::MovableStructure(Structure structure, glm::vec3 position, int ID, Button* p_button)
void GUI::PopStructure(unsigned int buttonID)
{
	if (buttonID < this->nButtons)
	{
		MovableStructure newStructure(buttons[buttonID].AssignedStructure(),
			buttons[buttonID].Position(), 
			(int) this->nStructures, 
			&buttons[buttonID]);

		structures.push_back(newStructure);
		this->nStructures++;
	}
}

void GUI::DroppedStructure(Button* p_button)
{
	if (p_button != NULL)
	{
		PopStructure(p_button->ID());
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
		//if (glm::distance(structures[i].Position(), _pointer.Position()) < DRAG_RADIUS && _pointer.Pinching())
		if (structures[i].CloseEnough(_pointer.Position()) && _pointer.Pinching())
		{
			_pointer.AssignStructure(&(structures[i]));
		}
	}
}

void GUI::UpdatePointer(bool mode)
{
	_pointer.update(mode);
}

void GUI::Update(bool mode)
{
	if (_init)
	{
		UpdatePointer(mode);
		CheckForPinchedStructure();
	}
}

void GUI::UpdateWorldMatrix(const glm::mat4& worldMatrix)
{
	_pointer.UpdateWorldMatrix(worldMatrix);
}