#include "HalfModule.hh"

/*HalfModule::HalfModule() : _x(0), _y(0), _z(0) 
{
	glm::vec3 position(_x, _y, _z);


	_hemisphere1.setOBJfile("Models/hemisphere.obj");
	_hemisphere2.setOBJfile("Models/hemisphere.obj");

	_hemisphere1.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
	_hemisphere1.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

	_hemisphere2.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
	_hemisphere2.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE))
		*glm::rotate(3.14f, glm::vec3(1.0f, 0.0f, 0.0f)));
}*/

/*HalfModule::HalfModule(int x, int y, int z) : _x(x), _y(y), _z(z)
{
	glm::vec3 position(_x, _y, _z);


	_hemisphere1.setOBJfile("Models/hemisphere.obj");
	_hemisphere2.setOBJfile("Models/hemisphere.obj");

	_hemisphere1.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
	_hemisphere1.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

	_hemisphere2.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
	_hemisphere2.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE))
		*glm::rotate(3.14f, glm::vec3(1.0f, 0.0f, 0.0f)));

}*/

void HalfModule::Init(int x, int y, int z)
{
	_x = x;
	_y = y;
	_z = z;

	glm::vec3 position(_x, _y, _z);
	position *= MODULE_SIZE;

	_hemisphere1.setOBJfile("Models/hemisphere_clean.obj");
	_hemisphere2.setOBJfile("Models/hemisphere_clean.obj");

	_hemisphere1.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
	_hemisphere1.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

	_hemisphere2.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "");
	_hemisphere2.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

}

void HalfModule::Draw(const glm::mat4& VP) const
{
	_hemisphere1.DrawWithLines(VP);
	_hemisphere2.DrawWithLines(VP);
}

glm::vec3 HalfModule::Position()
{
	return glm::vec3(_x, _y, _z);
}