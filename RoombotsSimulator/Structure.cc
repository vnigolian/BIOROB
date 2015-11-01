#include "Structure.hh"


Structure::Structure(glm::vec3 position, int ID, Button* p_button) :_position(position),_ID(ID), _p_button(p_button)
{
	this->_shadow.Init("Shaders/shadow_vshader.glsl", "Shaders/shadow_fshader.glsl", "");
	this->_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, -EYES_POSITION + 0.011f, _position.z))
		*glm::scale(glm::mat4(1.0f), glm::vec3(SHADOW_SIZE)));
	Init("");
	std::cout << _position.x << _position.y << _position.z << std::endl;
}

void Structure::Init(std::string sourceFilename)
{
	RoomBot module1;
	module1.Init(0, 0, 0, 
		         0, 1, 0);

	RoomBot module2;
	module2.Init(1, 0, 0, 
		         1, 1, 0);

	roomBots.push_back(module1);
	roomBots.push_back(module2);
}


void Structure::Drop()
{
	//When the Structure is dropped, we simply set the y-coordinate to the ground's y-coordinate 
	_moving = false;
	_position = glm::vec3(_position.x, -EYES_POSITION + 0.01f + MODULE_SIZE * 0.5f, _position.z);
	//_p_button->AddStructure();
}

void Structure::Drag(const glm::vec3& position)
{
	//we update the Structure's position to match the one passed in argument
	_moving = true;
	this->_position = position;

	this->_shadow.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(this->_position.x, -EYES_POSITION + 0.011f, this->_position.z))
		                        *glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
}

void Structure::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);

	for (size_t i = 0; i < roomBots.size();i++)
	{
		//we multiply the VP matrix by a translation to draw the modules at the right place
		roomBots[i].Draw(VP*glm::translate(glm::mat4(1.0f), _position));
	}
	//we only draw the shadow if the Structure is moving, 
	//allowing the user to see where the Structure will be dropped
	if (_moving)
	{
		this->_shadow.Draw(VP);
	}
	glDisable(GL_BLEND);
}

glm::vec3 Structure::Position() const
{
	return _position;
}

void Structure::CleanUp()
{
	_shadow.CleanUp();
}

Button* Structure::LinkedButton() const
{
	return _p_button;
}