#include "Button.hh"
#include "Structure.hh"



Button::Button(glm::vec3 position, unsigned int ID, Structure* p_structure) : _position(position), _ID(ID), _p_structure(p_structure)
{
	_model = new Cube("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "", glm::vec4(0.0f,0.0f,1.0f,1.0f));
	_model->SetModelMatrix(glm::translate(glm::mat4(1.0f), _position)*glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));

	_shadow = new Quad("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x,-EYES_POSITION+0.001f,_position.z))*glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));
	std::cout << "New button created with ID " << ID << std::endl;
}


void Button::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	_model->Draw(VP);
	_shadow->Draw(VP);
	glDisable(GL_BLEND);
}


void Button::CleanUp() const
{
	_model->CleanUp();
	_shadow->CleanUp();
	_p_structure->CleanUp();
	delete _p_structure;
}


Structure* Button::AssignedStructure() const
{
	return _p_structure;
}