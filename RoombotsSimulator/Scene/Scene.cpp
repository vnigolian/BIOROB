#include "Scene.hh"

void Scene::initRoof(double roomSize){
	_roof.Init("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/wood2.jpg");
	_roof.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 3.0, -roomSize / 2.0))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));
}


void Scene::AddModel(const Model& sourceModel)
{	
	models.push_back(sourceModel.copy());
	this->nModels += 1;
	//std::cout << "model's texture : " << models[nModels-1]->Texture() << "\n";
}

void const Scene::Render(const glm::mat4& VP, bool drawRoof)
{
	for (size_t i(0); i < this->nModels; i++)
	{
		models[i]->Draw(VP);
	}
	if (drawRoof){
		_roof.Draw(VP);
	}
}

/*Push the GL attribute bits so that we don't wreck any settings
glPushAttrib(GL_ALL_ATTRIB_BITS);

// Enable polygon offsets, and offset filled polygons forward by 2.5
glEnable(GL_POLYGON_OFFSET_FILL);
glPolygonOffset(-2.5f, -2.5f);

// Set the render mode to be line rendering with a thick line width
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
glLineWidth(3.0f);

// Set the colour to be white
glColor3f(1.0f, 1.0f, 1.0f);

// Render the object
RenderMesh3();

// Set the polygon mode to be filled triangles 
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glEnable(GL_LIGHTING);

// Set the colour to the background
glColor3f(0.0f, 0.0f, 0.0f);

// Render the object
RenderMesh3();

// Pop the state changes off the attribute stack
// to set things back how they were
glPopAttrib();
*/
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