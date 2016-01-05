#include "TrashCan.hh"

/*Creates a new TrashCan at the position passed by argument*/
TrashCan::TrashCan(glm::vec3 position) : d_position(glm::vec3(position.x, -EYES_POSITION + 0.001+TRASH_CAN_SIZE/2, position.z))
{
	d_model = new Cube("Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(0.7f, 0.7f, 0.7f, 0.2f));
	d_model->SetModelMatrix(glm::translate(glm::mat4(1.0f), d_position)*glm::scale(glm::mat4(1.0f), glm::vec3(TRASH_CAN_SIZE)));

}

/*Draws the TrashCan*/
void TrashCan::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	d_model->Draw(VP);
	glDisable(GL_BLEND);
}

/*Cleans up the Model representing the TrashCan*/
void TrashCan::CleanUp() const
{
	d_model->CleanUp();
	delete d_model;
}
