/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "Simulation.hh"

void Simulation::Initialize(const std::vector<Position> roombotsFinalPositions, PathFinder* pathFinder)
{
	Reset();

	int modulesPerLine = (int)(ROOM_SIZE / MODULE_SIZE);

	for (size_t i(0); i < roombotsFinalPositions.size() / 2; i++)
	{
		Position roombotInitialPosition = Position(glm::vec3(-ROOM_SIZE / 2 + MODULE_SIZE*(i % modulesPerLine),
			-EYES_POSITION + MODULE_SIZE,
			MODULE_SIZE * 2 * (i / modulesPerLine)));

		d_paths.push_back(Path());
		pathFinder->Run(d_paths[i], roombotInitialPosition, roombotsFinalPositions[i * 2]);
		d_paths[i].push_back(roombotsFinalPositions[i * 2 + 1]);
	}
	
	std::cout << "Paths for " << d_paths.size() << " Roombots have been computed with the path-finding algorithm called " << pathFinder->Name() << std::endl;

	OBJModel* hemisphere1 = new OBJModel("Models/hemisphere_10.obj", "Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	OBJModel* hemisphere2 = new OBJModel("Models/hemisphere_10.obj", "Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

	hemisphere1->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	hemisphere2->SetModelMatrix(glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

	glm::vec4 pale_green(0.66f, 0.66f, 0.18f, 1.0f);
	OBJModel* p_circle = new OBJModel("Models/circle_50.obj", "Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", pale_green);


	//for every path, we create and add two separate HalfModules. 
	//Every successive pair of HalfModules represents a Roombot
	for (size_t i(0); i < d_paths.size(); i++)
	{
		d_halfModules.push_back(HalfModule(d_paths[i][0], hemisphere1, hemisphere2, p_circle));
		d_halfModules.push_back(HalfModule(d_paths[i][1], hemisphere1, hemisphere2, p_circle));
	}

	d_init = true;
	d_over = false;

	//The reference clock is set to the current time
	d_refClock = clock();

	std::cout << "Simulation initialized. Ready to run !" << std::endl;
}

bool Simulation::NextStep()
{
	/*To run the Simulation, every step means to take a halfModule of every Roombot and move it to the next Position
	along the path. At every step, it changes which of the two HalfModules moves, also changing which one is used as pivot.
	Since all HalfModules look the same and there is no continuous movement, it often looks like all HalfModules are moved
	at the same time*/
	bool notOver = false;

	if (d_init)
	{
		std::cout << "processing step " << d_currentStep << std::endl;
		for (size_t i(0); i < d_paths.size(); i++)
		{			
			//For every path, we check if it is not over yet
			if (d_currentStep < d_paths[i].size())
			{
				/*if not, the Simulation is not over and we set the position of the current HalfModule 
				to the next position along the current path.
				The '2 * i' comes from the fact that one out of two HalfModules is the pivot and only the 
				other one is moving*/
				notOver = true;
				d_halfModules[2 * i + d_currentStep % 2].SetPosition(d_paths[i][d_currentStep] );
			}
		}
		d_currentStep++;

		if (!notOver){
			Reset();
		}
	}

	d_over = !notOver;
	return d_over;
}

void Simulation::Draw(const glm::mat4& VP)
{
	if (d_init)
	{
		for (size_t i(0); i < d_halfModules.size(); i++)
		{
			d_halfModules[i].Draw(VP);
		}
	}
}

void Simulation::Run()
{
	if (!d_over)
	{
		std::clock_t curTime = clock();
		
		double diff = ((float)(curTime - d_refClock))/CLOCKS_PER_SEC;
		//A step is executed only if 0.3 seconds have passed since the last step
		if (diff > 0.2)
		{
			NextStep();
			d_refClock = curTime;
		}
	}
}


void Simulation::Reset()
{
	if (d_init)
	{
		std::cout << "Resetting simulation" << std::endl;
	}

	//Since all Halfmodules use the same three Models to be drawn,
	//we only need to call 'CleanUp()' once
	if (!d_halfModules.empty())
	{
		d_halfModules[0].CleanUp();
	}
	d_paths.clear();
	d_halfModules.clear();
	d_currentStep = 0;
	d_init = false;
	d_over = true;
}
