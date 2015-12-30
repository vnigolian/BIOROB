#include "MovableStructure.hh"

int count = 0;

std::ostream& operator<<(std::ostream& os, glm::vec3 vec)
{
	os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
	return os;
}

MovableStructure::MovableStructure(Structure* p_structure, glm::vec3 position, int ID, unsigned int buttonID) : 
_p_structure(p_structure), _ID(ID), _buttonID(buttonID)
{
	setPosition(position);
	count++;
	std::cout << "count at : " << count << std::endl;
}

void MovableStructure::setPosition(glm::vec3 position)
{
	_position = Position(position - _p_structure->CenterOffset() + glm::vec3(MODULE_SIZE/2));
	std::cout << "structure positionned at " << position.x << " " << position.y << " " << position.z << " is now at "; _position.print();
}

void MovableStructure::Drag(const glm::vec3& position)
{
	//we update the Structure's position to match the one passed in argument
	_moving = true;
	setPosition(position);

	//this->_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(this->_position.x, -EYES_POSITION + 0.011f, this->_position.z))
	//                        *glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
}

void MovableStructure::Drop()
{
	//When the Structure is dropped, we simply set the y-coordinate to the ground's y-coordinate 
	_moving = false;
	setPosition(glm::vec3(_position.x()*MODULE_SIZE, -EYES_POSITION + 0.01f, _position.z()*MODULE_SIZE)
		+ _p_structure->CenterOffset() 
		- glm::vec3(MODULE_SIZE / 2, 0.0f, MODULE_SIZE / 2));

	_buttonID = -1;
	//std::cout << "dropped the Structure and now the ID is " << _buttonID << std::endl;
}
  
bool MovableStructure::CloseEnough(glm::vec3 position)
{
	return glm::distance(_position.toGLM(), position) < DRAG_RADIUS;
}



void MovableStructure::Draw(const glm::mat4& VP) const
{
	glm::vec3 scaledPosition = (_position *(1.0f / MODULE_SIZE)).toGLM();
	glm::vec3 discrete_position = glm::vec3(floor(scaledPosition.x), scaledPosition.y, floor(scaledPosition.z));
	discrete_position = MODULE_SIZE * discrete_position;
	//std::cout << "discrete_position : "<< discrete_position.x << " " << discrete_position.y << " " << discrete_position.z << " " << std::endl;
	if (_p_structure != NULL)
	{
		//_p_structure->Draw(VP*glm::translate(glm::mat4(1.0f), discrete_position));
		//std::cout << "drawing at " << (_position*MODULE_SIZE).toGLM().x << " " << (_position*MODULE_SIZE).toGLM().y << " " << (_position*MODULE_SIZE).toGLM().z << std::endl;;

		_p_structure->Draw(VP*glm::translate(glm::mat4(1.0f), _position.toGLM()*MODULE_SIZE));
	}
}

Position MovableStructure::getPosition() const
{
	return _position;
}

/*glm::vec3 MovableStructure::CenterPosition() const
{
	return _position + _structure.CenterOffset();
}*/

void MovableStructure::CleanUp()
{
}

unsigned int MovableStructure::LinkedButtonID() const
{
	return _buttonID;
}

std::vector<Position> MovableStructure::RoombotsPositions() const
{
	std::vector<Position> positions = _p_structure->RoombotsPositions();
	Position position = Position(_position);

	for (size_t i(0); i < positions.size(); i++)
	{
		positions[i] += position;
	}

	return positions;
}
