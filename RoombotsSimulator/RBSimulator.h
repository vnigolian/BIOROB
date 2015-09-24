#include "common.h"
#include "ShaderLoader.h"
#include "Models\Quad.h"

class RBSimulator{

	Quad floor_square;

	unsigned int width = 800;
	unsigned int height = 600;

	mat4 projectionMatrix;
	mat4 viewMatrix;

public:
	/*
mat4 PerspectiveProjection(float fovy, float aspect, float nearDistance, float farDistance);
mat4 OrthographicProjection(float left, float right, float bottom, float top, float nearDistance, float farDistance);
*/

	// Gets called when the windows is resized.
	void Resize(int w, int h);

	void Display();

	int Init(int argc, char **argv);

	void SetUp();

	unsigned int Width()
	{ 
		return width;
	}

	unsigned int Height(){
		return height;
	}

private:
};