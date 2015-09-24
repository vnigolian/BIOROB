#include "RBSimulator.h"

using namespace Core;

/*
mat4 PerspectiveProjection(float fovy, float aspect, float nearDistance, float farDistance){
// TODO 1: Create a perspective projection matrix given the field of view,
// aspect ratio, and near and far plane distances.
float top = nearDistance * tan(fovy/2);
float right = top * aspect;
mat4 projection = mat4(0.0);
projection[0][0] = nearDistance / right;
projection[1][1] = nearDistance / top;
projection[2][2] = -(farDistance + nearDistance) / (farDistance - nearDistance);
projection[3][2] = -1.0f;
projection[2][3] = (-2 * farDistance * nearDistance) / (farDistance - nearDistance);
return projection;
}

mat4 OrthographicProjection(float left, float right, float bottom, float top, float nearDistance, float farDistance){

mat4 ortho = mat4(0.0);
ortho[0][0] = 2.0f / (right - left);
ortho[1][1] = 2.0f / (top - bottom);
ortho[2][2] = -2.0f / (farDistance - nearDistance);
ortho[3][3] = 1.0f;
ortho[0][3] = -(right + left) / (right - left);
ortho[1][3] = -(top + bottom) / (top - bottom);
ortho[2][3] = -(farDistance + nearDistance) / (farDistance - nearDistance);
return ortho;
}*/

// Gets called when the windows is resized.
void RBSimulator::Resize(int w, int h) {
	width = w;
	height = h;

	std::cout << "Window has been resized to " << width << "x" << height << "." << std::endl;
	glViewport(0, 0, width, height);

	GLfloat top = 1.0f;
	GLfloat right = (GLfloat)width / height * top;
	GLfloat ratio = width / (GLfloat)height;
	projectionMatrix = glm::perspective(45.0f, ratio, 0.1f, 10.0f);
	//projectionMatrix = glm::ortho(-right, right, -top, top, -10.0f, 10.0f);
}

void RBSimulator::Display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Scaling matrix to scale the cube down to a reasonable size.
	mat4 cube_scale = { 0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.0, 0.0, 0.0, 1.0 };


	floor_square.Draw(projectionMatrix*viewMatrix*cube_scale);
	glutSwapBuffers();//switch between the two buffers
}


void RBSimulator::SetUp()
{

	glEnable(GL_DEPTH_TEST);

	floor_square.Init();

	vec3 cam_pos(0.0f, 1.0f, 2.0f);
	vec3 cam_look(0.0f, 0.0f, 0.0f);
	vec3 cam_up(0.0f, 1.0f, 0.0f);
	viewMatrix = glm::lookAt(cam_pos, cam_look, cam_up);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

int RBSimulator::Init(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);//allows to use depth, color and double buffering
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Roombots Simulator");

	GLenum err = glewInit();
	fprintf(stdout, "%s\n", glewGetErrorString(err));
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


	// register callbacks
	//glutDisplayFunc(Display);//sets 'Display' as the function to call when displaying
	//glutReshapeFunc(Resize);

	SetUp();

	glutMainLoop();//starts the openGL state machine

	floor_square.CleanUp();
	//glDeleteProgram(program);
	return 0;
}