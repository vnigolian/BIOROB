
#include "common.hh"
#include "ShaderLoader.hh"
#include "Scene\Quad.hh"
#include "Scene\Cube.hh"
#include "RiftHandler.hh"
#include "Scene\Scene.hh"

using namespace Core;
//using namespace OVR;
//using namespace std;
//using namespace glm;


Scene scene;

unsigned int width = 0;
unsigned int height = 0;

RiftHandler rift;


// Gets called when the windows is resized.
void Resize(int w, int h)
{
	//We want the window to be fixed-size (adapted to the Rift's display)
	glutReshapeWindow(width,height);
}

void RenderScene()
{
	glm::mat4 VP = rift.glmViewProjMatrix();

	scene.Render(VP);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rift.DisplayOnRift();

	glutSwapBuffers();//switch between the two buffers
	
}



void Init()
{
	glEnable(GL_DEPTH_TEST);
	Quad floor_quad;
	floor_quad.Init("Shaders/quad_vshader.glsl", "Shaders/quad_fshader.glsl", "Textures/wood2.jpg");
	floor_quad.SetModelMatrix(glm::scale(mat4(1.0f), vec3(10.0))*glm::translate(mat4(1.0f), vec3(0.0f, -0.5f, -1.0f)));

	Cube skybox;
	skybox.Init("Shaders/sky_vshader.glsl", "Shaders/sky_fshader.glsl", "Textures/skybox_texture.jpg");
	skybox.SetModelMatrix(glm::scale(mat4(1.0f), vec3(500.0f)));

	Cube testButton;
	testButton.Init("Shaders/button_vshader.glsl", "Shaders/button_fshader.glsl", "");
	testButton.SetModelMatrix(glm::scale(mat4(1.0f), vec3(0.1f))*glm::translate(mat4(1.0f), vec3(-0.5f,0.5f,-1.0f)));

	scene.AddModel(floor_quad);
	scene.AddModel(skybox);
	scene.AddModel(testButton);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//<------- LINE MODE

	rift.Init(RenderScene);

	//This sets the mirror window's size
	//The mirror window is the one that mirrors the Rift's display on the regular screen
	width = rift.ResolutionWidth() / 2;
	height = rift.ResolutionHeight() / 2;
	glutReshapeWindow(width, height);
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
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//allows to use depth, color and double buffering
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(0, 0); //it will be resized in Init();
	glutCreateWindow("RoomBots Simulator");

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
