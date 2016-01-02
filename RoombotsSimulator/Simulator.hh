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
#include "DirectPathFinder.hh"
#include "Simulation.hh"
#include <thread>

/**
   The Simulator class is the main class of the software and binds everything together.
   It is a singleton, as there's no need for multiple instances of it.
   It mainly contains the Scene and the Graphic User Interface and is in charge of handling all 
   windowing system-related components, as well as handling the Oculus Rift and initializing
   the Simulation and run it when ready.

   About the mode :
   The environment can interacted with through two modes, the 'Room-View' mode and the 'Box-View' mode.
   The first one is just as if the User was sitting in the room and the second is just as if the User was
   sitting in front of a small box containing the scene.
   The Room-View mode allows to move freely in the room by using the "WASD" keys and the Box-View mode
   allows to grab and drop Structures from containers called "Buttons"
*/

class Simulator {

	static Simulator d_instance;                 //The static instance of the Simulator, making it a singleton
	BrutePathFinder  d_pathFinder;               //The pathFinder used to create all the paths before Simulation
	Simulation       d_simulation;               //The Simulation that will run once the scene is set up
	Scene            d_scene;                    //The scene containing all the static elements of the environment	
	RiftHandler      d_rift;                     //The object allowing easy use of the Oculus Rift	
	GUI              d_GUI;                      //The Graphic User Interface allowing interaction with the environment
	unsigned int     d_width = 0;                //The window's width
	unsigned int     d_height = 0;               //The window's height
	glm::mat4        d_worldMatrix = glm::mat4();//The worldMatrix that changes depending on the current mode
	bool             d_mode = true;	             //viewing mode. false for "in-room" view, true for "box" view
	bool             d_running = true;           //Whether or not the Simulator is running
	int              d_windowID;                 //The OpenGL context window's ID

public:
	
	/*Returns the unique instance of the singleton Simulator*/
	static Simulator& Instance();

	/*Initializes the Simulator by passing the various callback functions as argument.
	- The first two are passed to the OpenGL-context creation function.
	
	- 'display' is the method that will be called at every rendering loop of the OpenGL context.
	
	- 'renderScene' is the method that will be called everytime the scene has to be drawn
	   
	- 'keyboardFunc' is the method that handles keystrokes
	
	- 'resizeFunc' is the method called everytime the window is resized*/
	void Init(int argc, 
		char **argv,
		DisplayFunction display,
		DisplayFunction renderScene, 
		void (*keyboardFunc)(unsigned char, int,int), 
		void (*resizeFunc)(int,int),
		void (*closeFunc)());

	/*Starts the Simulator*/
	void Start();

	/*Cleans up everything*/
	void CleanUp();

	/*Gets called when the windows is resized. It forces the window to a certain size*/
	void Resize(int w, int h);

	/*Renders everything*/
	void RenderScene();

	/*Displays the rendered scene into the Oculus Rift*/
	void Display();

	/*Handles the keystrokes. 
	IMPORTANT NOTE : This is based on the value of the pressed key on a QWERTZ keyboard.*/
	void HandleKeyboard(unsigned char key, 
		                int x, 
						int y);

	void Close();

	/*Returns the world matrix*/
	glm::mat4 WorldViewMatrix();

private:
	/*The constructor is private to ensure the singleton properties*/
	Simulator();
	~Simulator();

	/*All four following methods update the world matrix if the current mode is Room-View*/
	void Forward();

	void Left();

	void Backwards();

	void Right();
	//-------------------------------------------------------------------------------------

	/*Switches between modes*/
	void SwitchViewMode();

	/*Initializes the Scene*/
	void InitScene();

	/*Initializes the Oculus Rift*/
	void InitRift(DisplayFunction function);

	/*Initializes the Simulation*/
	void InitSimulation();

	/*this method allows us to have control over the main OpenGL context loop.
	we call one iteration of the loop ourself */
	void MainLoop();

	
};




