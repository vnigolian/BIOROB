#pragma once
#include "RoomBot.hh"
#include "BrutePathFinder.hh"
#include "PathFinder.hh"

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
	std::vector<Path>       d_paths;          ///<The vector of all the Roombots' path
	std::vector<HalfModule> d_halfModules;    ///<The vector of all halfModules that will move during Simulation
	unsigned int            d_currentStep = 0;///<The index of the current simulation step
	bool                    d_init = false;   ///<Whether or not the Simulation has been initialized
	bool                    d_over = true;    ///<Whether or not the Simulation is over. It is considered over when not initialized

	std::clock_t            d_refClock;       ///<The reference clock used to time the calls to 'nextStep()'



public:

	/**Initializes the Simulation.
	\arg \c roombotsFinalPositions A \c vector of all the Positions of all the Roombot
	\arg \c pathFinder The PathFinder to use to compute all the Path */
	void Initialize(const std::vector<Position> roombotsFinalPositions, PathFinder* pathFinder);

	/**Executes a step of the Simulation.
	Returns false if the simulation is over and true otherwise*/
	bool NextStep();

	/**Draws all modules needed to perform the Simulation*/
	void Draw(const glm::mat4& VP);

	/**Returns whether or not the simulation is over.*/
	bool IsOver(){ return d_over; }

	/**Returns whether or not the Simulation has been initialized*/
	bool IsInitialized(){ return d_init; }

	/**Executes one steps of the Simulation if it's not over and
	ensures the execution of the successive steps is well-timed*/
	void Run();

private:
	/**Resets the Simulation*/
	void Reset();
};

