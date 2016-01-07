#pragma once

#include "common.hh"
#include "Model.hh"
#include "Quad.hh"
#include "Cube.hh"

/**
*  The Scene contains all the Models used to represent the scene in which the simulation takes place.
*  The floor, the walls, the windows, the roof, the door and a skybox surrounding the room
*  Aside from the roof, all Models are added polymorphicly.
*  The roof get a special treatment because it is not necessarily drawn, depending on the current mode.
*/
class Scene
{
	std::vector<const Model*> d_models; ///<The models contained in the scene
	size_t                    d_nModels;///<The number of models in the scene
	Quad*                     d_roof;   ///<the roof

public:
	/**Initializes the Scene
	\arg \c roomSize the size of the room in the middle of the Scene*/
	void Init(float roomSize);
	
	/**Drawns all the elements of the Scene and the roof if the current mode is RoomView
	\arg \c VP the Projection-View matrix
	\arg \c drawRoof whether or not the roof should be drawn*/
	void const Render(const glm::mat4& VP, 
		              bool drawRoof);

	/**Cleans up all the Models of the Scene*/
	void CleanUp();

private:
	/**Adds a Model to the Scene
	\arg \c sourceModel The Model to add*/
	void AddModel(Model* sourceModel);

};