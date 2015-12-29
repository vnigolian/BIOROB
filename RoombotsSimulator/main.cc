
#include "common.hh"
#include "ShaderLoader.hh"
#include "Scene\Quad.hh"
#include "Scene\Cube.hh"
#include "RiftHandler.hh"
#include "Scene\Scene.hh"
#include "GUI.hh"
#include "Scene\OBJModel.hh"
#include "Simulator.hh"
#include "Scene\RoomBot.hh"

void display()
{
	(Simulator::Instance()).Display();
}

void renderScene()
{
	(Simulator::Instance()).RenderScene();
}

void handleKeyboard(unsigned char key, int x, int y)
{
	(Simulator::Instance()).HandleKeyboard(key, x, y);
}

void resize(int w, int h)
{
	(Simulator::Instance()).Resize(w, h);
}

int main(int argc, char **argv)
{
	//1er appel de Instance: on alloue le pointeur SoundManager::m_instance
	Simulator& p_simulator = Simulator::Instance();
	p_simulator.Init(argc, argv, display, renderScene, handleKeyboard, resize);
	p_simulator.start();
	p_simulator.CleanUp();

	return 0;
}


//using namespace OVR;
//using namespace std;
//using namespace glm;

/*
Scene _scene;

unsigned int width = 0;
unsigned int height = 0;

RiftHandler _rift;

GUI _GUI;

//viewing mode. false for "in-room" view, true for "box" view
bool _mode = true;

glm::mat4 _worldMatrix = glm::mat4();

void Forward()
{
	if (!_mode)
	{
		_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f));
	}
}

void Left()
{
	if (!_mode)
	{
		_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
	}
}

void Backwards()
{
	if (!_mode)
	{
		_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.2f));
	}
}

void Right()
{
	if (!_mode)
	{
		_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, 0.0f, 0.0f));
	}
}

// Gets called when the windows is resized.
void Resize(int w, int h)
{
	//We want the window to be fixed-size (adapted to the Rift's display)
	glutReshapeWindow(width,height);
}

glm::mat4 WorldViewMatrix()
{
	glm::mat4 worldViewMatrix = glm::mat4(1.0f);
	if (_mode)
	{
		worldViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.2f, -0.2f))
			*glm::scale(glm::mat4(1.0f), glm::vec3(1 / 12.0f));
	}
	return worldViewMatrix;
}

void RenderScene()
{
	glm::mat4 VP = glm::mat4(1.0f);
	if (_mode)
	{
		VP = _rift.glmViewProjMatrix() * WorldViewMatrix();
	}
	else
	{
		VP = _rift.glmViewProjMatrix() * _worldMatrix ;
	}
	_scene.Render(VP,!_mode);

	_GUI.Render(VP);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_rift.DisplayOnRift();

	glutSwapBuffers();//switch between the two buffers

}



void SwitchViewMode()
{
	_mode = _mode ^ true;
	if (_mode)
	{
		std::cout << "Box View" << std::endl;
	}
	else
	{
		std::cout << "Room View" << std::endl;
	}
}

void HandleKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w' : 
		Forward();
		break;
	case 'a' :
		Left();
		break;
	case 's' :
		Backwards();
		break;
	case 'd' :
		Right();
		break;
	case ' ' :
		SwitchViewMode();
		break;
	}
}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const float roomSize = 5.0f;

	Quad* floor_quad = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/wood2.jpg", glm::vec4(0.0f,0.0f,0.0f,0.0f));
	floor_quad->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, - EYES_POSITION, -roomSize / 2.0))
		                     *glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));

	Quad* left_wall1 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* left_wall2 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* left_wall3 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	left_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* right_wall1 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* right_wall2 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* right_wall3 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -EYES_POSITION + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));


	Quad* back_wall1 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* back_wall2 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* back_wall3 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

	Quad* front_wall1 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* front_wall2 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -EYES_POSITION + roomSize / 6.0, -0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
	Quad* front_wall3 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	front_wall3->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, 0.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));


	Quad* right_window1 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_window1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0 - 0.01, -EYES_POSITION + roomSize / 6.0, -roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* right_window2 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	right_window2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0 - 0.01, -EYES_POSITION + roomSize / 6.0, -2 * roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* back_window1 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_window1->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize + 0.015))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));

	Quad* back_window2 = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/window.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	back_window2->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -EYES_POSITION + roomSize / 6.0, -roomSize + 0.015))

		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6)));
	
	Quad* door = new Quad("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/wooden_door.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	door->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0 + 0.01, -EYES_POSITION + roomSize / 6.4, -roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 6.4,roomSize / 6.4, 2* roomSize/6.4)));
	
	Cube* skybox = new Cube("Shaders/sky_vshader.glsl", "Shaders/sky_fshader.glsl", "Textures/skybox_texture.jpg", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	skybox->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(50.0f)));

	_scene.AddModel(floor_quad);
	_scene.AddModel(skybox);

	_scene.AddModel(left_wall1);
	_scene.AddModel(left_wall2);
	_scene.AddModel(left_wall3);

	_scene.AddModel(right_wall1);
	_scene.AddModel(right_wall2);
	_scene.AddModel(right_wall3);

	_scene.AddModel(back_wall1);
	_scene.AddModel(back_wall2);
	_scene.AddModel(back_wall3);

	_scene.AddModel(front_wall1);
	_scene.AddModel(front_wall2);
	_scene.AddModel(front_wall3);

	_scene.AddModel(right_window1);
	_scene.AddModel(right_window2);
	_scene.AddModel(back_window1);
	_scene.AddModel(back_window2);
	_scene.AddModel(door);

	_scene.initRoof(roomSize);

	//roomBot.Init(0, 0, -1, 0, 1, -1);

	_rift.Init(RenderScene);

	//This sets the mirror window's size
	//The mirror window is the one that mirrors the Rift's display on the regular screen
	width = _rift.ResolutionWidth() / 2;
	height = _rift.ResolutionHeight() / 2;
	glutReshapeWindow(width, height);


	//GUI INIT
	_GUI.Init();

}


void CleanUp()
{
	_scene.CleanUp();
	_rift.CleanUp();
	_GUI.CleanUp();
}


//this method allows us to have control over the main OpenGL context loop.
//we call one iteration of the loop ourself

void MainLoop()
{
	while (true)
	{
		_GUI.UpdateWorldMatrix(_worldMatrix);
		_GUI.Update(_mode);// update the pointer's position by getting data from the LeapMotion sensor
		Display();//we call display at every iteration so that we update the view matrix depending on the Oculus' position
		glutMainLoopEvent();//executes one iteration of the OpenGL main loop
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//allows to use depth, color and double buffering
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(0, 0); //it will be resized in Init();
	glutCreateWindow("RoomBots Simulator");
	glutKeyboardFunc(HandleKeyboard);
	
	GLenum err = glewInit();
	if (!err)
	{
		fprintf(stdout, "GLEW init error : %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	Init();
	// register callbacks
	glutDisplayFunc(Display);//sets 'Display' as the function to call when displaying
	glutReshapeFunc(Resize);//sets 'Resize' as the function to cass when resizing

	MainLoop();//starts the main loop

	CleanUp();//cleans up everything
	return 0;
}*/




