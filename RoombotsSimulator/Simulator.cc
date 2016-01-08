/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "Simulator.hh"


Simulator Simulator::d_instance = Simulator();

Simulator::Simulator()
{
	std::cout << "Simulator created" << std::endl;
}


Simulator& Simulator::Instance()
{
	return d_instance;
}

Simulator::~Simulator() 
{
	CleanUp();
}

void Simulator::Init(int argc, 
	char **argv, 
	DisplayFunction display, 
	DisplayFunction renderScene, 
	void(*handleKeyboard)(unsigned char, int, int), 
	void(*resize)(int, int),
	void(*closeFunc)())
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//allows to use depth, color and double buffering
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(0, 0); //it will be resized in Init();
	d_windowID = glutCreateWindow("RoomBots Simulator");
	std::cout << "Created GLUT window with ID : " << d_windowID << std::endl;

	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	
	glutKeyboardFunc(handleKeyboard);
	glutDisplayFunc(display);//sets 'Display' as the function to call when displaying
	glutReshapeFunc(resize);//sets 'Resize' as the function to call when resizing
	glutCloseFunc(closeFunc);//sets 'Close' as the function to call when the window is closed

	GLenum err = glewInit();
	if (!err)
	{
		fprintf(stdout, "GLEW init error : %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	InitRift(renderScene);
	d_scene.Init(ROOM_SIZE);
	d_GUI.Init();

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Simulator::Close()
{
	std::cout << "Closing application..." << std::endl;
	glutLeaveMainLoop();
	std::cout << "Left GLUT main loop" << std::endl;
	glutDestroyWindow(d_windowID);
	std::cout << "Destroyed the window with ID : "<<d_windowID << std::endl;
	d_running = false;

	exit(EXIT_SUCCESS);
}

void Simulator::Start()
{
	MainLoop();
}



// Gets called when the windows is resized.
void Simulator::Resize(int w, int h)
{
	//We want the window to be fixed-size (adapted to the Rift's display)
	glutReshapeWindow(d_width, d_height);
}

glm::mat4 Simulator::WorldViewMatrix()
{
	glm::mat4 worldViewMatrix = glm::mat4(1.0f);
	if (d_mode)
	{
		worldViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.2f, -0.2f))
			*glm::scale(glm::mat4(1.0f), glm::vec3(1 / 12.0f));
	}
	return worldViewMatrix;
}

void Simulator::RenderScene()
{
	glm::mat4 VP = glm::mat4(1.0f);
	if (d_mode)
	{
		VP = d_rift.glmViewProjMatrix() * WorldViewMatrix();
	}
	else
	{
		VP = d_rift.glmViewProjMatrix() * d_worldMatrix;
	}
	d_scene.Render(VP, !d_mode);

	if (d_simulation.IsOver())
	{
		d_GUI.Render(VP);
	}
	else
	{
		d_simulation.Draw(VP);
	}
}

void Simulator::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	d_rift.DisplayOnRift();

	glutSwapBuffers();//switch between the two buffers

}



void Simulator::InitRift(DisplayFunction function){
	d_rift.Init(function);

	//This sets the mirror window's size
	//The mirror window is the one that mirrors the Rift's display on the regular screen
	d_width = d_rift.ResolutionWidth() / 2;
	d_height = d_rift.ResolutionHeight() / 2;
	glutReshapeWindow(d_width, d_height);
}



void Simulator::CleanUp()
{
	d_scene.CleanUp();
	d_rift.CleanUp();
	d_GUI.CleanUp();
}


void Simulator::MainLoop()
{
	
	while (d_running)
	{
		d_GUI.UpdateWorldMatrix(d_worldMatrix);
		d_GUI.Update(d_mode);// update the pointer's position by getting data from the LeapMotion sensor
		Display();//we call display at every iteration so that we update the view matrix depending on the Oculus' position
		
		d_simulation.Run();//The simulation step is actually executed only if it's already initialized
		glutMainLoopEvent();//executes one iteration of the OpenGL main loop
	}
}




void Simulator::Forward()
{
	if (!d_mode)
	{
		d_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f));
	}
}

void Simulator::Left()
{
	if (!d_mode)
	{
		d_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
	}
}

void Simulator::Backwards()
{
	if (!d_mode)
	{
		d_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.2f));
	}
}

void Simulator::Right()
{
	if (!d_mode)
	{
		d_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, 0.0f, 0.0f));
	}
}

void Simulator::SwitchViewMode()
{
	d_mode = d_mode ^ true;
	if (d_mode)
	{
		std::cout << "Box View" << std::endl;
	}
	else
	{
		std::cout << "Room View" << std::endl;
	}
}

void Simulator::HandleKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		Forward();
		break;
	case 'a':
		Left();
		break;
	case 's':
		Backwards();
		break;
	case 'd':
		Right();
		break;
	case 'q':
		d_GUI.RotateStructure(true);
		break;
	case 'e':
		d_GUI.RotateStructure(false);
		break;
	case ' ':
		SwitchViewMode();
		break;
	case 13:
		InitSimulation();
		break;
	
	default :
		std::cout << "you pressed : " << (int)key << std::endl;
	}
}

void Simulator::InitSimulation()
{
	std::cout << "launching simulation" << std::endl;

	BrutePathFinder* pathFinder = new BrutePathFinder();
	d_simulation.Initialize(d_GUI.GetAllRoombotsPositions(), pathFinder);
}




