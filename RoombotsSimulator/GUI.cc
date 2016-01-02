#include "GUI.hh"


void GUI::Init()
{
	//first, the LeapmotionPointer is initialized
	_pointer.Init(this);

	//then we set up the hemisphere models used by the Roombot modules
	OBJModel* hemisphere1 = new OBJModel("Models/hemis_with_holes_0.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	OBJModel* hemisphere2 = new OBJModel("Models/hemis_with_holes_0.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	
	hemisphere1->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	hemisphere2->SetModelMatrix(glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
	*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
	*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	
	//then we create new Structure based on .rbs files
	Structure* stool = new Structure("Structures/stool.rbs", hemisphere1,hemisphere2);
	Structure* chair = new Structure("Structures/chair.rbs", hemisphere1, hemisphere2);
	Structure* table = new Structure("Structures/table.rbs", hemisphere1, hemisphere2);

	//then we add buttons holding the Structures to the GUI
	AddButton(table);
	AddButton(stool);
	AddButton(chair);
	

	std::cout << "GUI initialized" << std::endl;
	_init = true;

	//<-------------------------------REMOVE THIS AT THE END
	MovableStructure testStructure(stool,_buttons[1].Position(),_nStructures,1);
	testStructure.Drop();
	_structures.push_back(testStructure);
	_nStructures++;

	MovableStructure testStructure2(chair, _buttons[2].Position(), _nStructures, 2);
	testStructure2.Drop();
	_structures.push_back(testStructure2);
	_nStructures++;


	MovableStructure testStructure3(table, _buttons[0].Position(), _nStructures, 0);
	testStructure3.Drop();
	_structures.push_back(testStructure3);
	_nStructures++;

	MovableStructure testStructure4(chair, glm::vec3(-ROOM_SIZE/3,0.0f,-2.0f), _nStructures, 2);
	testStructure4.Drop();
	_structures.push_back(testStructure4);
	_nStructures++;

	MovableStructure testStructure5(chair, glm::vec3(ROOM_SIZE / 3, 0.0f, -2.0f), _nStructures, 2);
	testStructure5.Drop();
	_structures.push_back(testStructure5);
	_nStructures++;

	MovableStructure testStructure6(chair, glm::vec3(-ROOM_SIZE / 4, 0.0f, -3.0f), _nStructures, 2);
	testStructure6.Drop();
	_structures.push_back(testStructure6);
	_nStructures++;

	MovableStructure testStructure7(table, glm::vec3(ROOM_SIZE / 5, 0.0f, -2.5f), _nStructures, 0);
	testStructure7.Drop();
	_structures.push_back(testStructure7);
	_nStructures++;

	MovableStructure testStructure8(chair, glm::vec3(-ROOM_SIZE / 3, 0.0f, -4.0f), _nStructures, 2);
	testStructure8.Drop();
	_structures.push_back(testStructure8);
	_nStructures++;

	MovableStructure testStructure9(chair, glm::vec3(ROOM_SIZE / 5, 0.0f, -2.5f), _nStructures, 2);
	testStructure9.Drop();
	_structures.push_back(testStructure9);
	_nStructures++;

	MovableStructure testStructure0(chair, glm::vec3(-ROOM_SIZE / 6, 0.0f, -1.0f), _nStructures, 2);
	testStructure0.Drop();
	_structures.push_back(testStructure0);
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

void GUI::PopStructure(unsigned int buttonID)
{
	if (buttonID < _nButtons)
	{
		std::cout << "Popping Structure on button with ID " << buttonID << std::endl;

		//What is actually created when popping a new Structure is a MovableStructure 
		//holding the corresponding Structure
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
	std::cout << "dropped structure with button ID " << buttonID << std::endl;
	PopStructure(buttonID);
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
	//we clean up all the buttons
	//NOTE : the structures are cleaned up through the buttons' clean-up
	for (size_t i(0); i < this->_nButtons; i++)
	{
		_buttons[i].CleanUp();
	}
	//and the pointer
	_pointer.CleanUp();
}

void GUI::CheckForPinchedStructure()
{
	//we look for the first MovableStructure in pinching range from the LeapmotionPointer while it is pinching
	for (size_t i(0); i < this->_nStructures; i++)
	{
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

std::vector<Position> GUI::GetAllRoombotsPositions()
{
	std::vector<Position> positions;

	//we start at '_nButtons' be cause we don't want to simulate the construction of
	//the Structures contained in the button, which are the first in '_structures'
	for (size_t i(_nButtons); i < _nStructures; i++)
	{
		std::vector<Position> structureRoombotsPositions = _structures[i].RoombotsPositions();
		positions.insert(positions.end(), structureRoombotsPositions.begin(), structureRoombotsPositions.end());
	}

	return positions;
}

