/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "MovableStructure.hh"


MovableStructure::MovableStructure(Structure* p_structure, glm::vec3 position, int ID, unsigned int buttonID) : 
d_p_structure(p_structure), d_ID(ID), d_buttonID(buttonID)
{
	SetPosition(position);
}

void MovableStructure::Rotate(bool left)
{
	if (left)
	{
		d_rotation++;
	}
	else
	{
		d_rotation--;
	}
}

void MovableStructure::SetPosition(glm::vec3 position)
{
	d_position = Position(position);
	//d_position = Position(position - d_p_structure->CenterOffset());

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
	SetPosition(glm::vec3(d_position.x()*MODULE_SIZE, -EYES_POSITION + 0.01f + d_p_structure->CenterOffset().y-MODULE_SIZE , d_position.z()*MODULE_SIZE));
		//+ d_p_structure->CenterOffset() 
		//- glm::vec3(MODULE_SIZE / 2, 0.0f, MODULE_SIZE / 2));

	d_buttonID = -1;
}
  
bool MovableStructure::CloseEnough(glm::vec3 position) const
{
	return CloseEnough(position,DRAG_RADIUS);
}

bool MovableStructure::CloseEnough(glm::vec3 position, float distance) const
{
	return glm::distance(MODULE_SIZE*(d_position.ToGLM()) + d_p_structure->CenterOffset() - glm::vec3(MODULE_SIZE / 2, MODULE_SIZE / 2, -MODULE_SIZE / 2), position) < distance;
}


void MovableStructure::Draw(const glm::mat4& VP) const
{
	if (d_p_structure != NULL)
	{
		//This matrix represents the rotation of the Structure on itself.
		//To perform such rotation, the Structure'center must be translated to the origin, 
		//then rotated around the vertical axis and finally put back at its original place
		glm::mat4 rotationMatrix(glm::translate(d_p_structure->CenterOffset())
			*glm::rotate(1.57f * d_rotation, glm::vec3(0.0f, 1.0f, 0.0f))
			*glm::translate(-d_p_structure->CenterOffset()));

		//The drawing accounts for the position of the MovableStructure 
		//and the self-rotation of the Structure
		d_p_structure->Draw(VP
			*glm::translate(glm::mat4(1.0f), d_position.ToGLM()*MODULE_SIZE)
			*rotationMatrix);
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

	//The glm::vec3, continuous position of the MovableStructure 
	//is converted into a discrete Position, thus mapping it onto the grid
	Position position = Position(d_position);

	for (size_t i(0); i < positions.size(); i++)
	{
		//We add the MovableStructure's discrete Position to the relative
		//Roombot's Positions to get their actual Position within the scene
		positions[i] += position;
	}

	return positions;
}

