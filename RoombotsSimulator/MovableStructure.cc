/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "MovableStructure.hh"


MovableStructure::MovableStructure(Structure* p_structure, glm::vec3 position, int ID, unsigned int buttonID) : 
d_ID(ID), d_buttonID(buttonID)
{
	if (p_structure != NULL)
	{
		d_p_structure = p_structure;
	}
	SetPosition(position);
}

void MovableStructure::Rotate(bool clockWise)
{
	if (clockWise)
	{
		d_rotation++;
	}
	else
	{
		d_rotation--;
	}
	d_rotation = d_rotation % 4;
}

void MovableStructure::SetPosition(glm::vec3 position)
{
	d_position = position - d_p_structure->CenterOffset();
}

void MovableStructure::Drag(const glm::vec3& position)
{
	//we update the Structure's position to match the one passed in argument
	d_moving = true;
	SetPosition(position);
}

void MovableStructure::Drop()
{
	//When the Structure is dropped, we simply set the y-coordinate to the ground's y-coordinate 
	d_moving = false;
	SetPosition(glm::vec3(d_position.x, - EYES_POSITION , d_position.z) + d_p_structure->CenterOffset());

	//std::cout << "dropped structure to position : " << d_position.x() << " " << d_p_structure->CenterOffset().y << " " << d_position.z() << std::endl;
	//std::cout << "dropped structure to position : " << d_position.x() << " " << d_position.y() << " " << d_position.z() << std::endl;
	d_buttonID = -1;
}
  
bool MovableStructure::CloseEnough(glm::vec3 position) const
{
	return CloseEnough(position,DRAG_RADIUS);
}

bool MovableStructure::CloseEnough(glm::vec3 position, float distance) const
{
	return glm::distance(d_position + d_p_structure->CenterOffset() - glm::vec3(MODULE_SIZE / 2, MODULE_SIZE / 2, -MODULE_SIZE / 2), position) < distance;
}


void MovableStructure::Draw(const glm::mat4& VP) const
{
	if (d_p_structure != NULL)
	{
		//The drawing accounts for the position of the MovableStructure 
		//and the self-rotation of the Structure
		d_p_structure->Draw(VP
			*glm::translate(Position(d_position).ToGLM() * MODULE_SIZE + d_p_structure->CenterOffset())
			*glm::rotate(1.57f * d_rotation,glm::vec3(0.0f,1.0f,0.0f)));
	}
}

Position MovableStructure::GetPosition() const
{
	return d_position;
}


unsigned int MovableStructure::LinkedButtonID() const
{
	return d_buttonID;
}

std::vector<Position> MovableStructure::RoombotsPositions() const
{
	//We get all the Roombot's relative Positions from the Structure
	std::vector<Position> positions = d_p_structure->RoombotsPositions();


	for (size_t i(0); i < positions.size(); i++)
	{
		//We add the MovableStructure's discrete Position to the relative
		//Roombot's Positions to get their actual Position within the scene
		positions[i] += d_position;
	}

	return positions;
}

