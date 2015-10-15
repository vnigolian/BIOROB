#include "common.hh"
#include "ShaderLoader.hh"
#include "Scene\Quad.hh"
#include "Scene\Cube.hh"
#include "RiftHandler.hh"
#include "Scene\Scene.hh"
#include "GUI.hh"

class Simulator
{

	Scene _scene;

	unsigned int _width = 0;
	unsigned int _height = 0;

	RiftHandler _rift;

	GUI _GUI;

	glm::mat4 _worldMatrix = glm::mat4();

	void InitScene();

	void Forward();

	void Left();

	void Backwards();

	void Right();

	void Resize(int w, int h);


	void RenderScene();

	void Display();


	void HandleKeyboard(unsigned char key, int x, int y);

	void CleanUp();

	void MainLoop();

public:
	void Init();
	void Start();

};