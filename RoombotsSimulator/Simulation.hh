#pragma once
#include "Scene\RoomBot.hh"
#include "BrutePathFinder.hh"

class Simulation
{
private:
	std::vector<Path> _paths;
	std::vector<HalfModule> _halfModules;
	unsigned int _currentStep = 0;
	bool _init = false;
	bool _over = true;

	void Reset();

public:
	void Initialize(const std::vector<Path>& paths);
	bool nextStep();
	void draw(const glm::mat4& VP);

	bool isOver(){ return _over; }
	bool isInitialized(){ return _init; }

	~Simulation();
};

