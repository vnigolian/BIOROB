#pragma once

#include "common.hh"
#include "ShaderLoader.hh"
#include "Scene\Quad.hh"
#include "Scene\Cube.hh"
#include "RiftHandler.hh"
#include "Scene\Scene.hh"
#include "GUI.hh"
#include "Scene\OBJModel.hh"
#include "Scene\RoomBot.hh"
#include "BrutePathFinder.hh"


class Simulator {
public:
	static Simulator& Instance();

	void Init(int argc, 
		char **argv,
		DisplayFunction display,
		DisplayFunction renderScene, 
		void (*keyboardFunc)(unsigned char, int,int), 
		void (*resizeFunc)(int,int));

	void start();

	void CleanUp();

	// Gets called when the windows is resized.
	void Resize(int w, int h);

	void RenderScene();

	void Display();

	void HandleKeyboard(unsigned char key, int x, int y);

private:
	static Simulator _instance;
	Simulator();
	~Simulator();

	Scene _scene;
	RiftHandler _rift;
	GUI _GUI;

	unsigned int width = 0;
	unsigned int height = 0;
	glm::mat4 _worldMatrix = glm::mat4();
	glm::mat4 WorldViewMatrix();

	bool _mode = true;	//viewing mode. false for "in-room" view, true for "box" view


	void Forward();

	void Left();

	void Backwards();

	void Right();

	void SwitchViewMode();

	void InitScene();

	void InitRift(DisplayFunction function);

	void launchSimulation();

	/*
	this method allows us to have control over the main OpenGL context loop.
	we call one iteration of the loop ourself
	*/
	void MainLoop();

	
};




