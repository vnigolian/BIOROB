#include "HalfModule.hh"
#include "../Position.hh"


HalfModule::HalfModule(int x, int y, int z, OBJModel* p_h1, OBJModel* p_h2): HalfModule(Position(x,y,z),p_h1,p_h2) {}

HalfModule::HalfModule(Position position, OBJModel* p_h1, OBJModel* p_h2) : _position(position)
{
	_hemisphere1 = p_h1;
	_hemisphere2 = p_h2;

	glm::vec4 pale_green(0.66f, 0.66f, 0.18f, 1.0f);

	_circle = new OBJModel("Models/circle.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
}



void HalfModule::Draw(const glm::mat4& VP) const
{
	glm::vec3 position(_position.x(), _position.y(), _position.z());
	position *= MODULE_SIZE;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 VPWithTranslate = VP*translationMatrix;
	

	_hemisphere1->Draw(VPWithTranslate);
	_hemisphere2->Draw(VPWithTranslate);
	
	
	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f));

	_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y - MODULE_SIZE / 2, position.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + MODULE_SIZE / 2, position.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + 0.001f, position.z + MODULE_SIZE / 2))
		*scale_matrix);

	_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + 0.001f, position.z - MODULE_SIZE / 2))
		*scale_matrix);

	_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x - MODULE_SIZE / 2, position.y, position.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);

	_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x + MODULE_SIZE / 2, position.y, position.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);
}



Position HalfModule::getPosition() const
{
	return _position;
}

void HalfModule::setPosition(const Position& position)
{
	_position = position;
}

