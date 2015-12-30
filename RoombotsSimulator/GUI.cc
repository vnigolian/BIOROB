#include "GUI.hh"


void GUI::Init()
{
	_pointer.Init(this);

	OBJModel* hemisphere1 = new OBJModel("Models/hemisphere_with_holes.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	OBJModel* hemisphere2 = new OBJModel("Models/hemisphere_with_holes.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	
	hemisphere1->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	hemisphere2->SetModelMatrix(glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
	*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
	*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	

	Structure* stool = new Structure("Structures/stool.rbs", hemisphere1,hemisphere2);
	Structure* chair = new Structure("Structures/chair.rbs", hemisphere1, hemisphere2);
	Structure* table = new Structure("Structures/table.rbs", hemisphere1, hemisphere2);
	
	/*Structure custom1("Structures/RB.rbs");
	Structure custom2("Structures/RB2.rbs");
	Structure custom3("Structures/RB3.rbs");
	Structure custom4("Structures/RB4.rbs");
	Structure custom5("Structures/RB8.rbs");
	*/

	AddButton(table);
	AddButton(stool);
	AddButton(chair);
	
	/*AddButton(custom1);
	AddButton(custom2);
	AddButton(custom3);
	AddButton(custom4);
	AddButton(custom5);
	*/
	std::cout << "GUI initialized" << std::endl;
	_init = true;

	MovableStructure testStructure(stool,_buttons[0].Position(),_nStructures,0);
	testStructure.Drop();
	_structures.push_back(testStructure);
	_nStructures++;

	MovableStructure testStructure2(chair, _buttons[1].Position(), _nStructures, 1);
	testStructure2.Drop();
	_structures.push_back(testStructure2);
	_nStructures++;

	MovableStructure testStructure3(table, _buttons[2].Position(), _nStructures, 2);
	testStructure3.Drop();
	_structures.push_back(testStructure3);
	_nStructures++;
}

void GUI::AddButton(Structure* p_structure)
{
	if (_nButtons <= 5)//we want max 5 buttons for now
	{
		//we make the position of the buttons vary to get a line of buttons
		glm::vec3 position = glm::vec3(BUTTON_LEFT_START - (this->_nButtons)*(BUTTON_SIZE + BUTTON_SEPARATION), BUTTON_UP_START, BUTTON_DEPTH_OFFSET);

		//we create the new Button with the position
		Button newButton(position, _nButtons, p_structure);
		_buttons.push_back(newButton);
		_nButtons++;
		//MovableStructure::MovableStructure(Structure structure, glm::vec3 position, int ID, Button* p_button) :

		//and add a structure linked to this button at the same position
		PopStructure(newButton.ID());
	}
}
//MovableStructure::MovableStructure(Structure structure, glm::vec3 position, int ID, Button* p_button)
void GUI::PopStructure(unsigned int buttonID)
{
	std::cout << "Popping Structure on button with ID " << buttonID << std::endl;
	if (buttonID < _nButtons)
	{
		MovableStructure newStructure(_buttons[buttonID].AssignedStructure(),
			_buttons[buttonID].Position(),
			_nStructures,
			buttonID);

		_structures.push_back(newStructure);
		_nStructures++;
	}
}

void GUI::DroppedStructure(unsigned int buttonID)
{
	
	if (buttonID<_nButtons)
	{
		std::cout << "dropped structure with button ID " << buttonID << std::endl;
		PopStructure(buttonID);
	}
}

void const GUI::Render(const glm::mat4& VP)
{
	if (_init)
	{
		//we draw all the structures
		for (size_t i(0); i < this->_nStructures; i++)
		{
			_structures[i].Draw(VP);
		}

		//all the buttons
		for (size_t i(0); i < this->_nButtons; i++)
		{
			_buttons[i].Draw(VP);
		}
		//and finally the LeapmotionPointer
		_pointer.Draw(VP);
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
	for (size_t i(0); i < this->_nStructures; i++)
	{
		_structures[i].CleanUp();
	}
}

void GUI::CheckForPinchedStructure()
{
	for (size_t i(0); i < this->_nStructures; i++)
	{
		//if (glm::distance(structures[i].Position(), _pointer.Position()) < DRAG_RADIUS && _pointer.Pinching())
		if (_structures[i].CloseEnough(_pointer.Position()) && _pointer.Pinching())
		{
			_pointer.AssignStructure(&(_structures[i]));
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

void GUI::disablePointer()
{
	_pointer.Disable();
}

void GUI::enablePointer()
{
	_pointer.Enable();
}

std::vector<Position> GUI::GetAllRoombotsPositions()
{
	std::vector<Position> positions;

	for (size_t i(_nButtons); i < _nStructures; i++)
	{
		std::vector<Position> structureRoombotsPositions = _structures[i].RoombotsPositions();
		positions.insert(positions.end(), structureRoombotsPositions.begin(), structureRoombotsPositions.end());
	}

	return positions;
}

