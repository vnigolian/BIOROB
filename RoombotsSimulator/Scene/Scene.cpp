#include "Scene.hh"


void Scene::AddModel(const Model& sourceModel)
{	
	models.push_back(sourceModel.copy());
	this->nModels += 1;
	//std::cout << "model's texture : " << models[nModels-1]->Texture() << "\n";
}

void const Scene::Render(const glm::mat4& VP)
{
	for (size_t i(0); i < this->nModels; i++)
	{
		models[i]->Draw(VP);
	}
}

size_t Scene::NModels()
{
	return this->nModels;
}

void Scene::CleanUp()
{
	for (size_t i(0); i < this->nModels; i++)
	{
		models[i]->CleanUp();
	}
}