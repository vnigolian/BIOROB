#include "GUI.hh"


/*GUI::GUI()
{
	_pointer.Init();
	AddButton();
	AddButton();
	AddButton();

}*/

void GUI::Init()
{
	AddPointer();
	//_rightPointer.Init(true);
	AddButton();
	AddButton();
	AddButton();
}

void GUI::AddButton()
{
	glm::vec3 position = glm::vec3(BUTTON_LEFT_OFFSET, BUTTON_UP_START - (this->_nButtons)*(BUTTON_SIZE+BUTTON_SEPARATION), BUTTON_DEPTH_OFFSET);

	Button newButton(position, (int) this->_nButtons);
	_buttons.push_back(newButton);
	this->_nButtons++;

	Structure newStructure(position, (int) this->_nStructures, &newButton);
	_structures.push_back(newStructure);
	this->_nStructures++;
}

void GUI::AddPointer()
{
	if (_nPointers == 0)
	{
		LeapmotionPointer newRightPointer;
		newRightPointer.Init(true);
		_pointers.push_back(newRightPointer);

		std::cout << "added right pointer" << std::endl;
		_nPointers++;
	}
	else if (_nPointers == 1)
	{
		LeapmotionPointer newLeftPointer;
		newLeftPointer.Init(false);
		_pointers.push_back(newLeftPointer);

		std::cout << "added left pointer" << std::endl;
		_nPointers++;
	}
}

void const GUI::Render(const glm::mat4& VP)
{
	for (size_t i(0); i < this->_nStructures; i++)
	{
		_structures[i].Draw(VP);
	}

	for (size_t i(0); i < this->_nButtons; i++)
	{
		_buttons[i].Draw(VP);
	}

	for (size_t i(0); i < this->_nPointers; i++)
	{
		_pointers[i].Draw(VP);
	}
	
}

size_t GUI::NButtons()
{
	return this->_nButtons;
}

void GUI::CleanUp()
{
	for (size_t i(0); i < this->_nButtons; i++)
	{
		_buttons[i].CleanUp();
	}
}

void GUI::CheckForPinchedStructure()
{
	for (size_t i(0); i < this->_nStructures; i++)
	{
		for (size_t j(0); j < this->_nPointers; j++)
		{
			if (glm::distance(_structures[i].Position(), _pointers[j].Position()) < DRAG_RADIUS && _pointers[j].Pinching())
			{
				_pointers[j].AssignStructure(&(_structures[i]));
			}
		}
	}
}

void GUI::UpdatePointer()
{
	for (size_t i(0); i < this->_nPointers; i++)
	{
		_pointers[i].update();
	}
}

void GUI::Update()
{
	UpdatePointer();
	CheckForPinchedStructure();
}
