#include "Button.hh"
#include "Structure.hh"



Button::Button(glm::vec3 position, 
	           unsigned int ID, 
			   Structure* p_structure) : d_position(position), d_ID(ID), d_p_structure(p_structure)
{
	d_model = new Cube("Shaders/simple_vshader.glsl", 
		               "Shaders/colorvec_fshader.glsl", 
					   "", 
					   glm::vec4(0.0f,0.0f,1.0f,0.3f));

	d_model->SetModelMatrix(glm::translate(glm::mat4(1.0f), d_position)
		                   *glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));

	d_shadow = new Quad("Shaders/simple_vshader.glsl", 
		                "Shaders/colorvec_fshader.glsl", 
						"", 
						glm::vec4(0.0f, 0.0f, 1.0f, 0.3f));

	d_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(d_position.x, -EYES_POSITION + 0.01f, d_position.z))
							*glm::scale(glm::mat4(1.0f), glm::vec3(BUTTON_SIZE)));

	std::cout << "New button created with ID " << ID << std::endl;
}


void Button::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	d_model->Draw(VP);
	d_shadow->Draw(VP);
	glDisable(GL_BLEND);
}


void Button::CleanUp() const
{
	d_model->CleanUp();
	d_shadow->CleanUp();
	delete d_p_structure;
}


Structure* Button::AssignedStructure() const
{
	return d_p_structure;
}