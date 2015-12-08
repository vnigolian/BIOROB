#include "MovableStructure.hh"

std::ostream& operator<<(std::ostream& os, glm::vec3 vec)
{
	os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
	return os;
}

MovableStructure::MovableStructure(Structure* p_structure, glm::vec3 position, int ID, unsigned int buttonID) : 
_p_structure(p_structure), _ID(ID), _buttonID(buttonID)
{
	setPosition(position);
	_shadow.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, -EYES_POSITION + 0.01f, _position.z))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	//std::cout << "New MovableStructure created with linked button with ID " << _buttonID <<" and center offset at " << _structure.CenterOffset()<< std::endl;
}

void MovableStructure::setPosition(glm::vec3 position)
{
	_position = position - _p_structure->CenterOffset() + glm::vec3(MODULE_SIZE/2);
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
	setPosition(glm::vec3(_position.x, -EYES_POSITION + 0.01f, _position.z) 
		+ _p_structure->CenterOffset() 
		- glm::vec3(MODULE_SIZE / 2, 0.0f, MODULE_SIZE / 2));

	//_p_button = NULL;
	_buttonID = -1;
	//std::cout << "dropped the Structure and now the ID is " << _buttonID << std::endl;
}
  
bool MovableStructure::CloseEnough(glm::vec3 position)
{
	return glm::distance(_position, position) < DRAG_RADIUS;
}



void MovableStructure::Draw(const glm::mat4& VP) const
{
	glm::vec3 scaledPosition = (1 / MODULE_SIZE) * _position;// CenterPosition();
	glm::vec3 discrete_position = glm::vec3(floor(scaledPosition.x), scaledPosition.y, floor(scaledPosition.z));
	discrete_position = MODULE_SIZE * discrete_position;
	//std::cout << "discrete_position : "<< discrete_position.x << " " << discrete_position.y << " " << discrete_position.z << " " << std::endl;

	if (_p_structure != NULL)
	{
		_p_structure->Draw(VP*glm::translate(glm::mat4(1.0f), discrete_position));
	}
	if (_moving)
	{
		//_shadow.Draw(VP*glm::translate(glm::mat4(1.0f), discrete_position));
	}
}

glm::vec3 MovableStructure::Position() const
{
	return _position;
}

/*glm::vec3 MovableStructure::CenterPosition() const
{
	return _position + _structure.CenterOffset();
}*/

void MovableStructure::CleanUp()
{
	_shadow.CleanUp();
}

unsigned int MovableStructure::LinkedButtonID() const
{
	return _buttonID;
}
