#include "GUI.hh"


void GUI::Init()
{
	//first, the LeapmotionPointer is initialized
	d_pointer.Init(this);

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
	d_init = true;

	//<-------------------------------REMOVE THIS AT THE END
	MovableStructure testStructure(stool,d_buttons[1].Position(),d_nStructures,1);
	testStructure.Drop();
	d_structures.push_back(testStructure);
	d_nStructures++;

	MovableStructure testStructure2(chair, d_buttons[2].Position(), d_nStructures, 2);
	testStructure2.Drop();
	d_structures.push_back(testStructure2);
	d_nStructures++;


	MovableStructure testStructure3(table, d_buttons[0].Position(), d_nStructures, 0);
	testStructure3.Drop();
	d_structures.push_back(testStructure3);
	d_nStructures++;

	MovableStructure testStructure4(chair, glm::vec3(-ROOM_SIZE/3,0.0f,-2.0f), d_nStructures, 2);
	testStructure4.Drop();
	d_structures.push_back(testStructure4);
	d_nStructures++;

	MovableStructure testStructure5(chair, glm::vec3(ROOM_SIZE / 3, 0.0f, -2.0f), d_nStructures, 2);
	testStructure5.Drop();
	d_structures.push_back(testStructure5);
	d_nStructures++;

	MovableStructure testStructure6(chair, glm::vec3(-ROOM_SIZE / 4, 0.0f, -3.0f), d_nStructures, 2);
	testStructure6.Drop();
	d_structures.push_back(testStructure6);
	d_nStructures++;

	MovableStructure testStructure7(table, glm::vec3(ROOM_SIZE / 5, 0.0f, -2.5f), d_nStructures, 0);
	testStructure7.Drop();
	d_structures.push_back(testStructure7);
	d_nStructures++;

	MovableStructure testStructure8(chair, glm::vec3(-ROOM_SIZE / 3, 0.0f, -4.0f), d_nStructures, 2);
	testStructure8.Drop();
	d_structures.push_back(testStructure8);
	d_nStructures++;

	MovableStructure testStructure9(chair, glm::vec3(ROOM_SIZE / 5, 0.0f, -2.5f), d_nStructures, 2);
	testStructure9.Drop();
	d_structures.push_back(testStructure9);
	d_nStructures++;

	MovableStructure testStructure0(chair, glm::vec3(-ROOM_SIZE / 6, 0.0f, -1.0f), d_nStructures, 2);
	testStructure0.Drop();
	d_structures.push_back(testStructure0);
	d_nStructures++;
}

void GUI::AddButton(Structure* p_structure)
{
	if (d_nButtons <= 5)//we want max 5 buttons for now
	{
		//we make the position of the buttons vary to get a line of buttons
		glm::vec3 position = glm::vec3(BUTTON_LEFT_START - (this->d_nButtons)*(BUTTON_SIZE + BUTTON_SEPARATION), BUTTON_UP_START, BUTTON_DEPTH_OFFSET);

		//we create the new Button with the position
		Button newButton(position, d_nButtons, p_structure);
		d_buttons.push_back(newButton);
		d_nButtons++;
		//MovableStructure::MovableStructure(Structure structure, glm::vec3 position, int ID, Button* p_button) :

		//and add a structure linked to this button at the same position
		PopStructure(newButton.ID());
	}
}

void GUI::PopStructure(unsigned int buttonID)
{
	if (buttonID < d_nButtons)
	{
		std::cout << "Popping Structure on button with ID " << buttonID << std::endl;

		//What is actually created when popping a new Structure is a MovableStructure 
		//holding the corresponding Structure
		MovableStructure newStructure(d_buttons[buttonID].AssignedStructure(),
			d_buttons[buttonID].Position(),
			d_nStructures,
			buttonID);

		d_structures.push_back(newStructure);
		d_nStructures++;
	}
}

void GUI::DroppedStructure(unsigned int buttonID)
{
	std::cout << "dropped structure with button ID " << buttonID << std::endl;
	PopStructure(buttonID);
}

void const GUI::Render(const glm::mat4& VP)
{
	if (d_init)
	{
		//we draw all the structures
		for (size_t i(0); i < this->d_nStructures; i++)
		{
			d_structures[i].Draw(VP);
		}

		//all the buttons
		for (size_t i(0); i < this->d_nButtons; i++)
		{
			d_buttons[i].Draw(VP);
		}
		//and finally the LeapmotionPointer
		d_pointer.Draw(VP);
	}
}

size_t GUI::NButtons()
{
	return this->d_nButtons;
}

void GUI::CleanUp()
{
	//we clean up all the buttons
	//NOTE : the structures are cleaned up through the buttons' clean-up
	for (size_t i(0); i < this->d_nButtons; i++)
	{
		d_buttons[i].CleanUp();
	}
	//and the pointer
	d_pointer.CleanUp();
}

void GUI::CheckForPinchedStructure()
{
	//we look for the first MovableStructure in pinching range from the LeapmotionPointer while it is pinching
	for (size_t i(0); i < this->d_nStructures; i++)
	{
		if (d_structures[i].CloseEnough(d_pointer.Position()) && d_pointer.Pinching())
		{
			d_pointer.AssignStructure(&(d_structures[i]));
		}
	}
}

void GUI::UpdatePointer(bool mode)
{
	d_pointer.update(mode);
}

void GUI::Update(bool mode)
{
	if (d_init)
	{
		UpdatePointer(mode);
		CheckForPinchedStructure();
	}
}

void GUI::UpdateWorldMatrix(const glm::mat4& worldMatrix)
{
	d_pointer.UpdateWorldMatrix(worldMatrix);
}

std::vector<Position> GUI::GetAllRoombotsPositions()
{
	std::vector<Position> positions;

	//we start at '_nButtons' be cause we don't want to simulate the construction of
	//the Structures contained in the button, which are the first in '_structures'
	for (size_t i(d_nButtons); i < d_nStructures; i++)
	{
		std::vector<Position> structureRoombotsPositions = d_structures[i].RoombotsPositions();
		positions.insert(positions.end(), structureRoombotsPositions.begin(), structureRoombotsPositions.end());
	}

	return positions;
}

