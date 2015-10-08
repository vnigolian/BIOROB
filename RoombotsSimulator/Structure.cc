#include "Structure.hh"


//Structure::Structure(glm::vec3 position, int ID, Button p_button) : _position(position), _ID(ID) {}//, _p_button(p_button) {}
Structure::Structure(glm::vec3 position, int ID, Button* p_button) : _position(position), _ID(ID), _p_button(p_button)
{
		this->_model.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
		this->_model.SetModelMatrix(glm::translate(mat4(1.0f), _position)*glm::scale(mat4(1.0f), vec3(MODULE_SIZE)));

		this->_shadow.Init("Shaders/shadow_vshader.glsl", "Shaders/shadow_fshader.glsl", "");
		this->_shadow.SetModelMatrix(glm::translate(mat4(1.0f), glm::vec3(_position.x, -1.199f, _position.z))*glm::scale(mat4(1.0f), vec3(MODULE_SIZE)));
}

//once it's dropped, it won't move and we displace it to the ground
void Structure::Drop()
{
	_position = glm::vec3(_position.x, MODULE_SIZE, _position.z);
	this->_model.SetModelMatrix(glm::scale(mat4(1.0f), vec3(MODULE_SIZE))*glm::translate(mat4(1.0f), this->_position));
	_moved = true;

}

void Structure::Drag(const glm::vec3& position)
{
	if (!_moved)
	{
		this->_position = position;
		this->_model.SetModelMatrix(glm::translate(mat4(1.0f), this->_position)*glm::scale(mat4(1.0f), vec3(MODULE_SIZE)));

		this->_shadow.SetModelMatrix(glm::translate(mat4(1.0f), glm::vec3(this->_position.x, -1.199f, this->_position.z))*glm::scale(mat4(1.0f), vec3(MODULE_SIZE)));
	}
}

void Structure::Draw(const glm::mat4& VP) const
{
	this->_model.Draw(VP);
	this->_shadow.Draw(VP);
	if (!_moved)
	{
		this->_shadow.Draw(VP);
	}
}


glm::vec3 Structure::Position() const
{
	return _position;
}