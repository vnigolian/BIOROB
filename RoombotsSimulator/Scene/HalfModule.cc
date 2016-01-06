/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "HalfModule.hh"
#include "../Position.hh"


HalfModule::HalfModule(int x, 
	                   int y, 
					   int z, 
					   OBJModel* p_h1, 
					   OBJModel* p_h2, 
					   OBJModel* p_circle) : HalfModule(Position(x, y, z), p_h1, p_h2, p_circle) {}

HalfModule::HalfModule(Position position, 
	                   OBJModel* p_h1, 
					   OBJModel* p_h2, 
					   OBJModel* p_circle) : d_position(position), d_p_hemisphere1(p_h1), d_p_hemisphere2(p_h2), d_p_circle(p_circle){}



void HalfModule::Draw(const glm::mat4& VP) const
{
	//Here, we compute the translation matrix representing the translation to the Module's position 
	//within the Structure that contains it
	glm::vec3 position(d_position.x(), d_position.y(), d_position.z());
	position *= MODULE_SIZE;
	position += glm::vec3(MODULE_SIZE / 2);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 VPWithTranslate = VP*translationMatrix;
	

	d_p_hemisphere1->Draw(VPWithTranslate);
	d_p_hemisphere2->Draw(VPWithTranslate);
	
	
	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE*0.65f));

	//Here, the same circle is drawn 6 times in different positions and orientations in order to draw all 6 faces
	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y - MODULE_SIZE / 2, position.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + MODULE_SIZE / 2, position.z - 0.005f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + 0.001f, position.z + MODULE_SIZE / 2))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y + 0.001f, position.z - MODULE_SIZE / 2))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x - MODULE_SIZE / 2, position.y, position.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);

	d_p_circle->Draw(VP*glm::translate(glm::mat4(1.0f), glm::vec3(position.x + MODULE_SIZE / 2, position.y, position.z + 0.001f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*scale_matrix);
}



Position HalfModule::GetPosition() const
{
	return d_position;
}

void HalfModule::SetPosition(const Position& position)
{
	d_position = position;
}


void HalfModule::CleanUp()
{
	d_p_circle->CleanUp();
	delete d_p_circle;

	d_p_hemisphere1->CleanUp();
	delete d_p_hemisphere1;

	d_p_hemisphere2->CleanUp();
	delete d_p_hemisphere2;
}

