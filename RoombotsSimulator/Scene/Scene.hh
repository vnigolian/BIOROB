#pragma once

#include "..\common.hh"
#include "Model.hh"

class Scene
{
	std::vector<const Model*> models;//The models contained in the scene
	size_t nModels;//The number of models in the scene

public:
	void AddModel(const Model& sourceModel);
	void const Render(const glm::mat4& VP);
	size_t NModels();
	void CleanUp();
};