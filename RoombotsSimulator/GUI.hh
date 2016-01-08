#pragma once

#include "Button.hh"
#include "LeapmotionPointer.hh"
#include "Structure.hh"
#include "Position.hh"
#include "TrashCan.hh"

/**The Graphic User Interface (GUI) regroups everything related to the manipulation of the environment.
It notably handles the LeapmotionPointer, the Buttons, the TrashCan and all MovableStructures.
It is also the link between all those elements*/
class GUI
{
	std::vector<const Button*>          d_buttons;        ///<The Buttons contained in the scene
	size_t                              d_nButtons = 0;   ///<The number of Buttons in the scene
	std::vector<MovableStructure*>      d_structures;     ///<The Structures contained in the scene
	size_t                              d_nStructures = 0;///<The number of Structures in the scene
	LeapmotionPointer                   d_pointer;        ///<The pointer using the Leapmotion device
	OBJModel*                           d_p_hemi1;        ///<The pointer to the first hemisphere Model
	OBJModel*                           d_p_hemi2;        ///<The pointer to the second hemisphere Model
	OBJModel*                           d_p_circle;       ///<The pointer to the circle Model
	TrashCan*                           d_trashCan;

public:
	
	/**Initializes the Graphic User Interface by initializing the LeapmotionPointer and adding Buttons*/
	void Init();

	/**Updates the positions of the Structures and the LeapmotionPointer
	\arg \c mode The current Simulator mode.*/
	void Update(bool mode);

	/**Updates the scene's world matrix. 
	  Used to change the behaviour of the LeapmotionPointer depending on the current mode*/
	void UpdateWorldMatrix(const glm::mat4& worldMatrix);

	/**Renders (draws) the Buttons, the Structures and the LeapmotionPointer*/
	void const Render(const glm::mat4& VP);

	/**Returns the number of Buttons in the GUI*/
	size_t NButtons();

	/**Notifies the GUI a Structure has been dropped and pops a new one 
	  on the corresponding button if the ID is valid
	  \arg \c buttonID The ID of the Button from which the dropped MovableStructure comes*/
	void DroppedStructure(unsigned int buttonID);

	/**Rotates the MovableStructure currently assigned to the LeapmotionPointer*/
	void RotateStructure(bool clockWise);

	/**Returns a vector of the positions of all the RoomBots*/
	std::vector<Position> GetAllRoombotsPositions();

	/**Cleans up everything*/
	void CleanUp();

private:

	/**Adds a button to the interface (max 3 for now)
	\arg \c  p_structure A pointer to the Structure that will be used to pop new 
	 MovableStructures from the added Button*/
	void AddButton(Structure* p_structure);

	/**Checks for every Structure if it is being pinched by the LeapmotionPointer*/
	void CheckForPinchedStructure();

	/**Updates the LeapmotionPointer's position depending on the Leapmotion Controller's data
	\arg \c mode the current Simulator mode*/
	void UpdatePointer(bool mode);

	/**Pops a new structure in a Button
	\arg \c buttonID The ID of the Button where to pop a new MovableStructure*/
	void PopStructure(unsigned int buttonID);
};