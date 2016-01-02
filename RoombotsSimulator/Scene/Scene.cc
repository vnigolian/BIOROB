#include "Scene.hh"

void Scene::InitRoof(float roomSize){
	d_roof = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/wood2.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	d_roof->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 3.0f, -roomSize / 2.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));
}


void Scene::AddModel(Model* sourceModel)
{	
	d_models.push_back(sourceModel);
	this->d_nModels += 1;
	//std::cout << "model's texture : " << models[nModels-1]->Texture() << "\n";
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

size_t Scene::NModels()
{
	return this->d_nModels;
}

void Scene::CleanUp()
{
	for (size_t i(0); i < this->d_nModels; i++)
	{
		d_models[i]->CleanUp();
	}
	d_roof->CleanUp();
}