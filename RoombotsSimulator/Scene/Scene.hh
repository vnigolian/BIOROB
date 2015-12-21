#pragma once

#include "..\common.hh"
#include "Model.hh"
#include "Quad.hh"

class Scene
{
	std::vector<const Model*> models;//The models contained in the scene
	size_t nModels;//The number of models in the scene
	Quad* _roof;

public:
	void initRoof(double roomSize);
	void AddModel(Model* sourceModel);
	void const Render(const glm::mat4& VP, bool drawRoof);
	size_t NModels();
	void CleanUp();
};