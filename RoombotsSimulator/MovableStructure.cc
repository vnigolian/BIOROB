#include "MovableStructure.hh"


MovableStructure::MovableStructure(Structure* p_structure, glm::vec3 position, int ID, unsigned int buttonID) : 
_p_structure(p_structure), _ID(ID), _buttonID(buttonID)
{
	setPosition(position);
}

void MovableStructure::setPosition(glm::vec3 position)
{
	_position = Position(position - _p_structure->CenterOffset() + glm::vec3(MODULE_SIZE/2));
}

void MovableStructure::Drag(const glm::vec3& position)
{
	//we update the Structure's position to match the one passed in argument
	_moving = true;
	setPosition(position);
}

void MovableStructure::Drop()
{
	//When the Structure is dropped, we simply set the y-coordinate to the ground's y-coordinate 
	_moving = false;
	setPosition(glm::vec3(_position.x()*MODULE_SIZE, -EYES_POSITION + 0.01f, _position.z()*MODULE_SIZE)
		+ _p_structure->CenterOffset() 
		- glm::vec3(MODULE_SIZE / 2, 0.0f, MODULE_SIZE / 2));

	_buttonID = -1;
}
  
bool MovableStructure::CloseEnough(glm::vec3 position)
{
	return glm::distance(_position.toGLM(), position) < DRAG_RADIUS;
}



void MovableStructure::Draw(const glm::mat4& VP) const
{
	//We want MovableStructures to be bound to a Roombot-sized grid and thus discretize their actual position
	glm::vec3 scaledPosition = (_position *((float)( 1.0f / MODULE_SIZE))).toGLM();
	glm::vec3 discrete_position = glm::vec3(floor(scaledPosition.x), scaledPosition.y, floor(scaledPosition.z));
	discrete_position = MODULE_SIZE * discrete_position;

	if (_p_structure != NULL)
	{
		_p_structure->Draw(VP*glm::translate(glm::mat4(1.0f), _position.toGLM()*MODULE_SIZE));
	}
}

Position MovableStructure::getPosition() const
{
	return _position;
}


unsigned int MovableStructure::LinkedButtonID() const
{
	return _buttonID;
}

std::vector<Position> MovableStructure::RoombotsPositions() const
{
	//We get all the Roombot's relative Positions from the Structure
	std::vector<Position> positions = _p_structure->RoombotsPositions();

	//The glm::vec3, continuous position of the MovableStructure 
	//is converted into a discrete Position, thus mapping it onto the grid
	Position position = Position(_position);

	for (size_t i(0); i < positions.size(); i++)
	{
		//We add the MovableStructure's discrete Position to the relative
		//Roombot's Positions to get their actual Position within the scene
		positions[i] += position;
	}

	return positions;
}

