/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "Scene.hh"

//Scene::Scene(float roomSize)
void Scene::Init(float roomSize)
{

	Quad* floor_quad = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex5_fshader.glsl", "Textures/wood2.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	floor_quad->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION, -roomSize / 2.0))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));

	Quad* left_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* left_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* left_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* right_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* right_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* right_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));


	Quad* back_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* back_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* back_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* front_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* front_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 6.0, -0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* front_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, 0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* right_window1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_window1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0 - 0.01, -EYES_POSITION + roomSize / 6.0, -roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* right_window2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_window2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0 - 0.01, -EYES_POSITION + roomSize / 6.0, -2 * roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* back_window1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_window1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize + 0.015))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* back_window2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_window2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize + 0.015))

		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* door = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/wooden_door.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	door->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0 + 0.01, -EYES_POSITION + roomSize / 6.4, -roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6.4, roomSize / 6.4, 2 * roomSize / 6.4)));

	Cube* skybox = new Cube("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/skybox_texture.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	skybox->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(50.0f)));

	d_roof = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex5_fshader.glsl", "Textures/wood2.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	d_roof->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 3.0f, -roomSize / 2.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));

	AddModel(floor_quad);
	AddModel(skybox);

	AddModel(left_wall1);
	AddModel(left_wall2);
	AddModel(left_wall3);

	AddModel(right_wall1);
	AddModel(right_wall2);
	AddModel(right_wall3);

	AddModel(back_wall1);
	AddModel(back_wall2);
	AddModel(back_wall3);

	AddModel(front_wall1);
	AddModel(front_wall2);
	AddModel(front_wall3);

	AddModel(right_window1);
	AddModel(right_window2);
	AddModel(back_window1);
	AddModel(back_window2);

	AddModel(door);
}


void Scene::AddModel(Model* sourceModel)
{	
	d_models.push_back(sourceModel);
	this->d_nModels ++;
}

void const Scene::Render(const glm::mat4& VP, bool drawRoof)
{
	for (size_t i(0); i < this->d_nModels; i++)
	{
		d_models[i]->Draw(VP);
	}
	if (drawRoof){
		d_roof->Draw(VP);
	}
}

void Scene::CleanUp()
{
	for (size_t i(0); i < this->d_nModels; i++)
	{
		d_models[i]->CleanUp();
		delete d_models[i];
	}
	d_roof->CleanUp();
	delete d_roof;
}