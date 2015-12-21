
#include "Simulator.hh"

void Simulator::Forward()
{
	_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f));
	_GUI.UpdateWorldMatrix(_rift.glmViewProjMatrix()*_worldMatrix);
}

void Simulator::Left()
{
	_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
	_GUI.UpdateWorldMatrix(_rift.glmViewProjMatrix()*_worldMatrix);
}

void Simulator::Backwards()
{
	_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.2f));
	_GUI.UpdateWorldMatrix(_rift.glmViewProjMatrix()*_worldMatrix);
}

void Simulator::Right()
{
	_worldMatrix *= glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, 0.0f, 0.0f));
	_GUI.UpdateWorldMatrix(_rift.glmViewProjMatrix()*_worldMatrix);
}

// Gets called when the windows is resized.
void Simulator::Resize(int w, int h)
{
	//We want the window to be fixed-size (adapted to the Rift's display)
	glutReshapeWindow(_width, _height);
}


void Simulator::RenderScene()
{
	glm::mat4 VP = _rift.glmViewProjMatrix()*_worldMatrix;

	_scene.Render(VP,false);

	_GUI.Render(VP);
}

void Simulator::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_rift.DisplayOnRift();

	glutSwapBuffers();//switch between the two buffers

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
	}
}

void Simulator::InitScene()
{
/*const float roomSize = 10.0f;
const float eyesPosition = 1.2f;

Quad floor_quad;
floor_quad.Init("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/wood2.jpg");
floor_quad.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -eyesPosition, -roomSize / 2.0))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize)));

Quad left_wall1;
left_wall1.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
left_wall1.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
Quad left_wall2;
left_wall2.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
left_wall2.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
Quad left_wall3;
left_wall3.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
left_wall3.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));

Quad right_wall1;
right_wall1.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
right_wall1.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
Quad right_wall2;
right_wall2.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
right_wall2.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
Quad right_wall3;
right_wall3.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
right_wall3.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));


Quad back_wall1;
back_wall1.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
back_wall1.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-roomSize / 2 + roomSize / 6, -eyesPosition + roomSize / 6.0, -roomSize))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
Quad back_wall2;
back_wall2.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
back_wall2.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -eyesPosition + roomSize / 6.0, -roomSize))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));
Quad back_wall3;
back_wall3.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
back_wall3.SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(roomSize / 2 - roomSize / 6, -eyesPosition + roomSize / 6.0, -roomSize))
*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
*glm::scale(glm::mat4(1.0f), glm::vec3(roomSize / 3)));


Cube skybox;
skybox.Init("Shaders/sky_vshader.glsl", "Shaders/sky_fshader.glsl", "Textures/skybox_texture.jpg");
skybox.SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(50.0f)));

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
_scene.AddModel(back_wall3);*/
}

void Simulator::Init(int argc, char** argv, void(*display)(void), void(*resize)(int, int), void(*keyboard)(unsigned char, int, int), void(*riftDisplay)(void))
{
	glutKeyboardFunc(keyboard);
	_rift.Init(riftDisplay);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//allows to use depth, color and double buffering
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(0, 0); //it will be resized in Init();
	glutCreateWindow("RoomBots Simulator");

	//glutKeyboardFunc(&(this->HandleKeyboard)); <----------------------------------------------------------

	GLenum err = glewInit();
	if (!err)
	{
		fprintf(stdout, "GLEW init error : %s\n", glewGetErrorString(err));
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitScene();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//<------- LINE MODE

	//_rift.Init(this->RenderScene);<----------------------------------------------------------

	//This sets the mirror window's size
	//The mirror window is the one that mirrors the Rift's display on the regular screen
	_width = _rift.ResolutionWidth() / 2;
	_height = _rift.ResolutionHeight() / 2;
	glutReshapeWindow(_width, _height);


	//GUI INIT
	_GUI.Init();

	// register callbacks
	//glutDisplayFunc(this->Display);//sets 'Display' as the function to call when displaying<----------------------------------------------------------
	//glutReshapeFunc(this->Resize);//sets 'Resize' as the function to cass when resizing<----------------------------------------------------------
}


void Simulator::CleanUp()
{
	_scene.CleanUp();
	_rift.CleanUp();
	_GUI.CleanUp();
}

/*this method allows us to have control over the main OpenGL context loop.
we call one iteration of the loop ourself*/

void Simulator::MainLoop()
{
	while (true)
	{
		glutMainLoopEvent();//executes one iteration of the OpenGL main loop
		Display();//we call display at every iteration so that we update the view matrix depending on the Oculus' position
		_GUI.Update(false);// update the pointer's position by getting data from the LeapMotion sensor
		_GUI.UpdateWorldMatrix(_worldMatrix);
	}
}

void Simulator::Start()
{
	MainLoop();
	CleanUp();
}


/*void Simulator::SetCallbacks(void(*display)(void), void(*resize)(int, int), void(*keyboard)(unsigned char, int, int), void(*riftDisplay)(void))
{
	glutKeyboardFunc(keyboard);
	_rift.Init(riftDisplay);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
}*/

/*
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
}
*/