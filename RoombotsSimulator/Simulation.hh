#pragma once
#include "Scene\RoomBot.hh"
#include "BrutePathFinder.hh"
#include <ctime>
#include <thread>
#include <future>

/**
   The Simulation encapsulates all that is needed to simulate the movements of the Roombot modules and
   allows to see how they would move around in the room to take their final place in the scene the User 
   would have previously set up.
   It runs in parallel with the rest of the software once initialized but does not use any concurrent 
   feature such as "std::thread".

   IMPORTANT NOTE : All modules and their path must be retreive outside of the Simulation and must be 
   given to it when initialized.
*/
class Simulation
{
private:
	std::vector<Path> _paths;//The vector of all the Roombots' path
	std::vector<HalfModule> _halfModules;//The vector of all halfModules that will move during Simulation
	unsigned int _currentStep = 0;//The index of the current simulation step
	bool _init = false;//Whether or not the Simulation has been initialized
	bool _over = true;//Whether or not the Simulation is over. It is considered over when not initialized

	std::clock_t _refClock;//The reference clock used to time the calls to 'nextStep()'

	/*Resets the Simulation*/
	void Reset();

public:
	/*Initializes the Simulation by passing the paths for all Modules by argument*/
	void Initialize(const std::vector<Path>& paths);

	/*Executes a step of the Simulation.
	Returns false if the simulation is over and true otherwise*/
	bool nextStep();

	/*Draws all modules needed to perform the Simulation*/
	void draw(const glm::mat4& VP);

	/*Returns whether or not the simulation is over.*/
	bool isOver(){ return _over; }

	/*Returns whether or not the Simulation has been initialized*/
	bool isInitialized(){ return _init; }

	/*Executes one steps of the Simulation if it's not over and
	ensures the execution of the successive steps is well-timed*/
	void run();

};

