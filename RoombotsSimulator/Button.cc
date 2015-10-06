#include "Button.hh"

//copy constructor
Button::Button(const Button& sourceButton) : _model(*(sourceButton._model.copy())), _position(sourceButton._position)
{
	_structure.Init(_position);
}

//this constructo just takes a position and sets up the button's graphical representation based on it
Button::Button(glm::vec3 position, int ID) : _position(position), _ID(ID)
{
	_model.Init("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "");
	_model.SetModelMatrix(glm::scale(mat4(1.0f), vec3(BUTTON_SIZE))*glm::translate(mat4(1.0f), _position));

	_structure.Init(_position);
}

/*
void Button::Init(glm::vec3 position, int ID)
{
	_position = position;
	_ID = ID;

	_model.Init("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "");
	_model.SetModelMatrix(glm::scale(mat4(1.0f), vec3(BUTTON_SIZE))*glm::translate(mat4(1.0f), _position));

	_structure.Init(glm::vec3(1.0f, 2.0f, -2.0f));
}*/

void Button::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	_structure.Draw(VP);
	_model.Draw(VP);
	glDisable(GL_BLEND);
}

void Button::CheckIfClicked(glm::vec3 position, bool pinching)
{
	//std::cout << "distance between pointer and structure " << _ID << " : " << glm::distance(_structure.Position(), position) << std::endl;
	//std::cout << "pointer : (" << _position.x << "," << _position.y << "," << _position.z << ")" << " button : (" << position.x << "," << position.y << "," << position.z << ")" << std::endl;
	if (glm::distance(_structure.Position(),position) < BUTTON_RADIUS && pinching)
	{
		_structure.Drag(position);
	}
}


void Button::Click() const
{
	std::cout << "Button " << _ID << " has been clicked !" << std::endl;
}

void Button::CleanUp() const
{
	_model.CleanUp();
}