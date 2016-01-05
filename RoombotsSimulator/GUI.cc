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
	
	glm::vec4 pale_green(0.66f, 0.66f, 0.18f, 1.0f);
	OBJModel* p_circle = new OBJModel("Models/circle_5.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);

	d_p_hemi1 = hemisphere1;
	d_p_hemi2 = hemisphere2;
	d_p_circle = p_circle;

	//then we create new Structure based on .rbs files
	Structure* stool = new Structure("Structures/stool.rbs", hemisphere1,hemisphere2, p_circle);
	Structure* chair = new Structure("Structures/chair.rbs", hemisphere1, hemisphere2, p_circle);
	Structure* table = new Structure("Structures/table.rbs", hemisphere1, hemisphere2, p_circle);

	//then we add buttons holding the Structures to the GUI
	AddButton(table);
	AddButton(stool);
	AddButton(chair);
	
	d_trashCan = new TrashCan(TrashCanPosition());

	std::cout << "GUI initialized" << std::endl;
	d_init = true;

}

void GUI::AddButton(Structure* p_structure)
{
	if (d_nButtons <= 5)//we want max 5 buttons for now
	{
		//we make the position of the buttons vary to get a line of buttons
		glm::vec3 position = glm::vec3(BUTTON_LEFT_START - (this->d_nButtons)*(BUTTON_SIZE + BUTTON_SEPARATION), BUTTON_UP_START, BUTTON_DEPTH_OFFSET);

		//we create the new Button with the position
		Button* newButton = new Button(position, d_nButtons, p_structure);
		d_buttons.push_back(newButton);
		d_nButtons++;

		//and add a structure linked to this button at the same position
		PopStructure(newButton->ID());
	}
}

void GUI::PopStructure(unsigned int buttonID)
{
	if (buttonID < d_nButtons)
	{
		std::cout << "Popping Structure on button with ID " << buttonID << std::endl;

		//What is actually created when popping a new Structure is a MovableStructure 
		//holding the corresponding Structure
		MovableStructure* newStructure = new MovableStructure(d_buttons[buttonID]->AssignedStructure(),
			d_buttons[buttonID]->Position(),
			d_nStructures,
			buttonID);

		d_structures.push_back(newStructure);
		d_nStructures++;
	}
}

void GUI::DroppedStructure(unsigned int buttonID)
{
	PopStructure(buttonID);
	size_t i(0);
	while( i<d_nStructures)
	{
		if (d_structures[i]->CloseEnough(d_trashCan->Position(), TRASH_CAN_SIZE))
		{
			delete d_structures[i];
			d_structures.erase(d_structures.begin() + i);
			d_nStructures--;
		}
		i++;
	}
}

void const GUI::Render(const glm::mat4& VP)
{
	if (d_init)
	{
		//we draw all the structures
		for (size_t i(0); i < this->d_nStructures; i++)
		{
			d_structures[i]->Draw(VP);
		}

		//all the buttons
		for (size_t i(0); i < this->d_nButtons; i++)
		{
			d_buttons[i]->Draw(VP);
		}
		//the TrashCan
		d_trashCan->Draw(VP);

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
	for (size_t i(0); i < this->d_nButtons; i++)
	{
		d_buttons[i]->CleanUp();
		delete d_buttons[i];
	}

	//the three Models used for the RoomBots
	d_p_hemi1->CleanUp();
	delete d_p_hemi1;
	d_p_hemi2->CleanUp();
	delete d_p_hemi2;
	d_p_circle->CleanUp();
	delete d_p_circle;

	//delete all structures
	for (size_t i(0); i < d_nStructures; i++)
	{
		delete d_structures[i];
	}

	//the trashCan
	d_trashCan->CleanUp();
	delete d_trashCan;

	//and the pointer
	d_pointer.CleanUp();
}

void GUI::CheckForPinchedStructure()
{
	//we look for the first MovableStructure in pinching range from the LeapmotionPointer while it is pinching
	for (size_t i(0); i < this->d_nStructures; i++)
	{
		if (d_structures[i]->CloseEnough(d_pointer.Position()) && d_pointer.Pinching())
		{
			d_pointer.AssignStructure((d_structures[i]));
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

	for (size_t i(0); i < d_nStructures; i++)
	{
		//We don't want to draw the Structures that are in the buttons, which are the ones
		//that have a valid linkedButtonID
		if (d_structures[i]->LinkedButtonID() >= d_nButtons)
		{
			std::vector<Position> structureRoombotsPositions = d_structures[i]->RoombotsPositions();
			positions.insert(positions.end(), structureRoombotsPositions.begin(), structureRoombotsPositions.end());
		}
	}

	return positions;
}

