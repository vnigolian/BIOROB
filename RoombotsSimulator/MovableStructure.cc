#include "MovableStructure.hh"


MovableStructure::MovableStructure(Structure structure, glm::vec3 position, int ID, Button* p_button) : 
_structure(structure), _position(position), _ID(ID), _p_button(p_button)
{
	_shadow.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, -EYES_POSITION + 0.01f, _position.z))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
}

void MovableStructure::SetLinkedButton(Button* p_button)
{
	_p_button = p_button;
}


void MovableStructure::Drop()
{
	//When the Structure is dropped, we simply set the y-coordinate to the ground's y-coordinate 
	_moving = false;
	_position = glm::vec3(_position.x, -EYES_POSITION + 0.01f + MODULE_SIZE * 0.5f, _position.z);
	_p_button = NULL;
}

bool MovableStructure::CloseEnough(glm::vec3 position)
{
	return glm::distance(CenterPosition(), position) < DRAG_RADIUS;
	//return glm::distance(_position, position) < DRAG_RADIUS;
}

void MovableStructure::Drag(const glm::vec3& position)
{
	//we update the Structure's position to match the one passed in argument
	_moving = true;
	this->_position = position - (_structure.CenterOffset());

	//this->_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(this->_position.x, -EYES_POSITION + 0.011f, this->_position.z))
	//                        *glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
}

void MovableStructure::Draw(const glm::mat4& VP) const
{
	glm::vec3 scaledPosition = (1 / MODULE_SIZE) * _position;// CenterPosition();
	glm::vec3 discrete_position = glm::vec3(floor(scaledPosition.x), scaledPosition.y, floor(scaledPosition.z));
	discrete_position = MODULE_SIZE * discrete_position;
	//std::cout << "discrete_position : "<< discrete_position.x << " " << discrete_position.y << " " << discrete_position.z << " " << std::endl;

	_structure.Draw(VP*glm::translate(glm::mat4(1.0f), discrete_position));
	if (_moving)
	{
		_shadow.Draw(VP);
	}
}

glm::vec3 MovableStructure::Position() const
{
	return _position;
}

glm::vec3 MovableStructure::CenterPosition() const
{
	return _position + _structure.CenterOffset();
}

void MovableStructure::CleanUp()
{
	_shadow.CleanUp();
}

Button* MovableStructure::LinkedButton() const
{
	return _p_button;
}
