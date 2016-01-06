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

Simulator::~Simulator(){
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

	InitScene();

	InitRift(renderScene);

	d_GUI.Init();

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



void Simulator::InitScene()
{
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const float roomSize = 5.0f;

	Quad* floor_quad = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex5_fshader.glsl", "Textures/wood2.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	floor_quad->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION, -roomSize / 2.0))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));

	Quad* left_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* left_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* left_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* right_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* right_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* right_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));


	Quad* back_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* back_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* back_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* front_wall1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* front_wall2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 6.0, -0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* front_wall3 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, 0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* right_window1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_window1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0 - 0.01, -EYES_POSITION + roomSize / 6.0, -roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* right_window2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_window2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0 - 0.01, -EYES_POSITION + roomSize / 6.0, -2 * roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* back_window1 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_window1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize + 0.015))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* back_window2 = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_window2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize + 0.015))

		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* door = new Quad("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/wooden_door.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	door->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0 + 0.01, -EYES_POSITION + roomSize / 6.4, -roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6.4, roomSize / 6.4, 2 * roomSize / 6.4)));

	Cube* skybox = new Cube("Shaders/simple_vshader.glsl", "Shaders/tex_fshader.glsl", "Textures/skybox_texture.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	skybox->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(50.0f)));

	d_scene.AddModel(floor_quad);
	d_scene.AddModel(skybox);

	d_scene.AddModel(left_wall1);
	d_scene.AddModel(left_wall2);
	d_scene.AddModel(left_wall3);

	d_scene.AddModel(right_wall1);
	d_scene.AddModel(right_wall2);
	d_scene.AddModel(right_wall3);

	d_scene.AddModel(back_wall1);
	d_scene.AddModel(back_wall2);
	d_scene.AddModel(back_wall3);

	d_scene.AddModel(front_wall1);
	d_scene.AddModel(front_wall2);
	d_scene.AddModel(front_wall3);

	d_scene.AddModel(right_window1);
	d_scene.AddModel(right_window2);
	d_scene.AddModel(back_window1);
	d_scene.AddModel(back_window2);
	d_scene.AddModel(door);

	d_scene.InitRoof(roomSize);

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

	std::vector<Position> roombotsFinalPositions = d_GUI.GetAllRoombotsPositions();

	std::cout << "All Roombots positions acquired" << std::endl;
	std::vector<Path> paths;

	int modulesPerLine = (int) (ROOM_SIZE / MODULE_SIZE);

	for (size_t i(0); i < roombotsFinalPositions.size()/2; i++)
	{
		Position roombotInitialPosition = Position(glm::vec3(-ROOM_SIZE / 2 + MODULE_SIZE*(i % modulesPerLine), 
			-EYES_POSITION + MODULE_SIZE, 
			MODULE_SIZE * 2 * (i / modulesPerLine)));

		paths.push_back(Path());
		d_pathFinder.Run(paths[i], roombotInitialPosition, roombotsFinalPositions[i * 2]);
		paths[i].push_back(roombotsFinalPositions[i * 2 + 1]);
	}
	std::cout << "Paths for " << paths.size() << " Roombots have been computed with the path-finding algorithm called " << d_pathFinder.Name() << std::endl;

	d_simulation.Initialize(paths);
}




