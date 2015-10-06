#include "Button.hh"

//copy constructor
Button::Button(const Button& sourceButton) : _model(*(sourceButton._model.copy())), _position(sourceButton._position){}

//this constructo just takes a position and sets up the button's graphical representation based on it
Button::Button(glm::vec3 position, int ID) : _position(position), _ID(ID)
{
	_model.Init("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "");
	_model.SetModelMatrix(glm::scale(mat4(1.0f), vec3(BUTTON_SIZE))*glm::translate(mat4(1.0f), _position));
}

void Button::Draw(const glm::mat4& VP) const
{

	glEnable(GL_BLEND);
	_model.Draw(VP);
	glDisable(GL_BLEND);
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