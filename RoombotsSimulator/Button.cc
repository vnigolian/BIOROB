#include "Button.hh"

//copy constructor
Button::Button(const Button& sourceButton) : _model(*(sourceButton._model.copy())), _position(sourceButton._position){}

//this constructo just takes a position and sets up the button's graphical representation based on it
Button::Button(glm::vec3 position, int ID) : _position(position), _ID(ID)
{
	std::cout << "button init" << std::endl;
	_model.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	_model.SetModelMatrix(glm::scale(mat4(1.0f), vec3(0.05f))*glm::translate(mat4(1.0f), _position));
	std::cout << "matrix scaled" << std::endl;
}

void Button::Draw(const glm::mat4& VP) const
{
	_model.Draw(VP);
}

void Button::CheckIfClicked(glm::vec3 position) const
{
	if (std::sqrt(glm::dot(position, _position)) < BUTTON_RADIUS)
	{
		Click();
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