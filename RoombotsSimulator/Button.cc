#include "Button.hh"

//copy constructor
/*Button::Button(const Button& sourceButton) : _model(*(sourceButton._model.copy())), _position(sourceButton._position)
{	
}*/

//this constructo just takes a position and sets up the button's graphical representation based on it
Button::Button(glm::vec3 position, int ID) : _position(position), _ID(ID), _model("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "")
{
	_model.SetModelMatrix(glm::translate(mat4(1.0f), _position)*glm::scale(mat4(1.0f), vec3(BUTTON_SIZE)));
}

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