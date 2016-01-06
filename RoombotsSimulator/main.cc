/**
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "Simulator.hh"

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

void close()
{
	(Simulator::Instance()).Close();
}

int main(int argc, char **argv)
{
	Simulator& p_simulator = Simulator::Instance();
	p_simulator.Init(argc, argv, display, renderScene, handleKeyboard, resize, close);
	p_simulator.Start();
	p_simulator.CleanUp();

	return 0;
}