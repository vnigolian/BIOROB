#include "Button.hh"
#include "Structure.hh"
//copy constructor
/*Button::Button(const Button& sourceButton) : _model(*(sourceButton._model.copy())), _position(sourceButton._position)
{	
	this->_shadow.Init("Shaders/shadow_vshader.glsl", "Shaders/shadow_fshader.glsl", "");
	this->_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, -EYES_POSITION + 0.01f, _position.z))*glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));
}*/

//this constructo just takes a position and sets up the button's graphical representation based on it
Button::Button(glm::vec3 position, unsigned int ID, Structure structure) : _position(position), _ID(ID), _structure(structure)
{
	_model.Init("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "");
	_model.SetModelMatrix(glm::translate(glm::mat4(1.0f), _position)*glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));
	std::cout << "New button created with ID " << ID << std::endl;
}


//Button::Button(glm::vec3 position, int ID, Structure structure);


void Button::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	_model.Draw(VP);
	//_shadow.Draw(VP);
	glDisable(GL_BLEND);
}

void Button::CheckIfClicked(glm::vec3 position, bool pinching)
{
	//std::cout << "distance between pointer and structure " << _ID << " : " << glm::distance(_structure.Position(), position) << std::endl;
	//std::cout << "pointer : (" << _position.x << "," << _position.y << "," << _position.z << ")" << " button : (" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
}


void Button::CleanUp() const
{
	_model.CleanUp();
}

glm::vec3 Button::Position() const
{
	return this->_position;
}

Structure Button::AssignedStructure() const
{
	return _structure;
}