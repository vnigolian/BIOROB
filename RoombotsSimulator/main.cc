
#include "common.hh"
#include "ShaderLoader.hh"
#include "Scene\Quad.hh"
#include "Scene\Cube.hh"
#include "RiftHandler.hh"
#include "Scene\Scene.hh"
#include "GUI.hh"

using namespace Core;
//using namespace OVR;
//using namespace std;
//using namespace glm;


Scene scene;

unsigned int width = 0;
unsigned int height = 0;

RiftHandler rift;

GUI _GUI;

glm::mat4 _worldMatrix = glm::mat4();

void Forward()
{
	_worldMatrix *= glm::translate(mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f));
}

void Left()
{
	_worldMatrix *= glm::translate(mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f));
}

void Backwards()
{
	_worldMatrix *= glm::translate(mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.2f));
}

void Right()
{
	_worldMatrix *= glm::translate(mat4(1.0f), glm::vec3(-0.2f, 0.0f, 0.0f));
}

// Gets called when the windows is resized.
void Resize(int w, int h)
{
	//We want the window to be fixed-size (adapted to the Rift's display)
	glutReshapeWindow(width,height);
}


void RenderScene()
{
	glm::mat4 VP = rift.glmViewProjMatrix()*_worldMatrix;

	scene.Render(VP);

	_GUI.Render(VP);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rift.DisplayOnRift();

	glutSwapBuffers();//switch between the two buffers

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
	}
}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const float roomSize = 10.0f;
	const float eyesPosition = 1.2f;

	Quad floor_quad;
	floor_quad.Init("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/wood2.jpg");
	floor_quad.SetModelMatrix(glm::translate(mat4(1.0f), vec3(0.0f, -eyesPosition, -roomSize / 2.0))*glm::scale(mat4(1.0f), vec3(roomSize)));

	Quad left_wall1;
	left_wall1.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	left_wall1.SetModelMatrix(glm::translate(mat4(1.0f), vec3(-roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize/3)));
	Quad left_wall2;
	left_wall2.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	left_wall2.SetModelMatrix(glm::translate(mat4(1.0f), vec3(-roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));
	Quad left_wall3;
	left_wall3.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	left_wall3.SetModelMatrix(glm::translate(mat4(1.0f), vec3(-roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));

	Quad right_wall1;
	right_wall1.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	right_wall1.SetModelMatrix(glm::translate(mat4(1.0f), vec3(roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));
	Quad right_wall2;
	right_wall2.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	right_wall2.SetModelMatrix(glm::translate(mat4(1.0f), vec3(roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - roomSize / 3.0))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));
	Quad right_wall3;
	right_wall3.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	right_wall3.SetModelMatrix(glm::translate(mat4(1.0f), vec3(roomSize / 2.0, -eyesPosition + roomSize / 6.0, -roomSize / 6.0 - 2.0 * (roomSize / 3.0)))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));


	Quad back_wall1;
	back_wall1.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	back_wall1.SetModelMatrix(glm::translate(mat4(1.0f), vec3(-roomSize/2 + roomSize/6, -eyesPosition + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));
	Quad back_wall2;
	back_wall2.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	back_wall2.SetModelMatrix(glm::translate(mat4(1.0f), vec3(0.0f, -eyesPosition + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize / 3)));
	Quad back_wall3;
	back_wall3.Init("Shaders/quad_vshader.glsl", "Shaders/quad2_fshader.glsl", "Textures/brick1.jpg");
	back_wall3.SetModelMatrix(glm::translate(mat4(1.0f), vec3(roomSize/2 - roomSize/6, -eyesPosition + roomSize / 6.0, -roomSize))
		*glm::rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f))
		*glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::scale(mat4(1.0f), vec3(roomSize/3)));


	Cube skybox;
	skybox.Init("Shaders/sky_vshader.glsl", "Shaders/sky_fshader.glsl", "Textures/skybox_texture.jpg");
	skybox.SetModelMatrix(glm::scale(mat4(1.0f), vec3(50.0f)));

	scene.AddModel(floor_quad);
	scene.AddModel(skybox);

	scene.AddModel(left_wall1);
	scene.AddModel(left_wall2);
	scene.AddModel(left_wall3);

	scene.AddModel(right_wall1);
	scene.AddModel(right_wall2);
	scene.AddModel(right_wall3);

	scene.AddModel(back_wall1);
	scene.AddModel(back_wall2);
	scene.AddModel(back_wall3);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//<------- LINE MODE

	rift.Init(RenderScene);

	//This sets the mirror window's size
	//The mirror window is the one that mirrors the Rift's display on the regular screen
	width = rift.ResolutionWidth() / 2;
	height = rift.ResolutionHeight() / 2;
	glutReshapeWindow(width, height);


	
	//GUI INIT
	_GUI.Init();

}


void CleanUp()
{
	scene.CleanUp();
	rift.CleanUp();
}

/*
this method allows us to have control over the main OpenGL context loop.
we call one iteration of the loop ourself
*/
void MainLoop()
{
	while (true)
	{
		glutMainLoopEvent();//executes one iteration of the OpenGL main loop
		Display();//we call display at every iteration so that we update the view matrix depending on the Oculus' position
		_GUI.Update();// update the pointer's position by getting data from the LeapMotion sensor
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
}
