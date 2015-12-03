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

void HalfModule::Init(int x, int y, int z, OBJModel* p_h1, OBJModel* p_h2)
{
	_x = x;
	_y = y;
	_z = z;

	glm::vec3 position(_x, _y, _z);
	position *= MODULE_SIZE;

	_hemisphere1 = p_h1;
	_hemisphere2 = p_h2;

	/*_hemisphere1.setOBJfile("Models/hemisphere_with_holes.obj");
	_hemisphere2.setOBJfile("Models/hemisphere_with_holes.obj");

	_hemisphere1.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "",glm::vec4(0.2f,0.2f,0.2f,1.0f));
	_hemisphere1.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

	_hemisphere2.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	_hemisphere2.SetModelMatrix(glm::translate(glm::mat4(1.0f), position)
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
*/
	glm::vec4 pale_green(0.66f, 0.66f, 0.18f, 1.0f);

	_circle1.setOBJfile("Models/circle.obj");
	_circle1.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
	_circle1.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y - MODULE_SIZE / 2, position.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f)));

	_circle2.setOBJfile("Models/circle.obj");
	_circle2.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
	_circle2.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + MODULE_SIZE / 2, position.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f)));

	_circle3.setOBJfile("Models/circle.obj");
	_circle3.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
	_circle3.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + 0.001f, position.z + MODULE_SIZE / 2))
		//*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f)));

	_circle4.setOBJfile("Models/circle.obj");
	_circle4.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
	_circle4.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + 0.001f, position.z - MODULE_SIZE / 2))
		//*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f)));

	_circle5.setOBJfile("Models/circle.obj");
	_circle5.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
	_circle5.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(position.x - MODULE_SIZE / 2, position.y, position.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f)));

	_circle6.setOBJfile("Models/circle.obj");
	_circle6.Init("Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", pale_green);
	_circle6.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(position.x + MODULE_SIZE / 2, position.y, position.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f)));


}

void HalfModule::Draw(const glm::mat4& VP) const
{
	glm::vec3 position(_x, _y, _z);
	position *= MODULE_SIZE;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 VPWithTranslate = VP*translationMatrix;
	

	_hemisphere1->Draw(VPWithTranslate);
	_hemisphere2->Draw(VPWithTranslate);
	_circle1.Draw(VP);
	_circle2.Draw(VP);
	_circle3.Draw(VP);
	_circle4.Draw(VP);
	_circle5.Draw(VP);
	_circle6.Draw(VP);
}

/*void HalfModule::Move(int x, int y, int z)
{
	_x = x;
	_y = y;
	_z = z;
}*/

glm::vec3 HalfModule::Position() const
{
	return glm::vec3(_x, _y, _z);
}