#include "Simulation.hh"


void Simulation::Initialize(const std::vector<Path>& paths)
{
	Reset();

	_paths = paths;

	OBJModel* hemisphere1 = new OBJModel("Models/hemisphere_with_holes.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	OBJModel* hemisphere2 = new OBJModel("Models/hemisphere_with_holes.obj", "Shaders/module_vshader.glsl", "Shaders/module_fshader.glsl", "", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

	hemisphere1->SetModelMatrix(glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));
	hemisphere2->SetModelMatrix(glm::rotate(1.57f, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(3.14f, glm::vec3(.0f, 0.0f, 1.0f))
		*glm::scale(glm::mat4(1.0f), glm::vec3(MODULE_SIZE)));

	for (size_t i(0); i < paths.size(); i++)
	{
		_halfModules.push_back(HalfModule(paths[i][0], hemisphere1, hemisphere2));
		_halfModules.push_back(HalfModule(paths[i][1], hemisphere1, hemisphere2));
	}

	_init = true;
	_over = false;

	std::cout << "Simulation initialized. Ready to run !" << std::endl;
}

bool Simulation::nextStep()
{
	bool notOver = false;

	if (_init)
	{
		std::cout << "processing step " << _currentStep << std::endl;
		for (size_t i(0); i < _paths.size(); i++)
		{			if (_currentStep < _paths[i].size())
			{
				notOver = true;
				_halfModules[2 * i + _currentStep % 2].setPosition(_paths[i][_currentStep] );
			}
		}

		_currentStep++;

		if (!notOver){
			Reset();
		}
	}

	_over = !notOver;
	return _over;
}

void Simulation::draw(const glm::mat4& VP)
{
	if (_init)
	{
		for (size_t i(0); i < _halfModules.size(); i++)
		{
			_halfModules[i].Draw(VP);
		}
	}
}

Simulation::~Simulation()
{
}

void Simulation::Reset()
{
	if (_init)
	{
		std::cout << "Resetting simulation" << std::endl;
	}
	_paths.clear();
	_halfModules.clear();
	_currentStep = 0;
	_init = false;
	_over = true;
}
