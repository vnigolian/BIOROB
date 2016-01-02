#pragma once

#include "..\common.hh"
#include "Model.hh"
#include "Quad.hh"

/**
   The Scene contains all the Models used to represent the scene in which the simulation takes place.
   The floor, the walls, the windows, the roof, etc.
   Aside from the roof, all Models are added polymorphicly and thus must be carefuly declared,
   initialized and added from outside, in the 'Simulator' class.
   The roof get a special treatment because it is not necessarily drawn, depending on the current mode.
*/
class Scene
{
	std::vector<const Model*> d_models; //The models contained in the scene
	size_t                    d_nModels;//The number of models in the scene
	Quad*                     d_roof;   //the roof

public:
	/*Initializes the Quad that represents the roof*/
	void InitRoof(float roomSize);

	/*Adds a Model to the list of elements of the Scene*/
	void AddModel(Model* sourceModel);
	/*Drawns all the elements of the Scene and the roof if the current mode is RoomView*/
	void const Render(const glm::mat4& VP, bool drawRoof);

	/*Returns the number of Models contained in the Scene*/
	size_t NModels();

	/*Cleans up all the Models of the Scene*/
	void CleanUp();
};