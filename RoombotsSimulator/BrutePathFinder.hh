/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once
#include "PathFinder.hh"

/*
	This PathFinder uses a very simple path-finding algorithm : 
	It simply goes to the same z-coordinate than the final position, 
	then to the same x-coordinate and finally to the same y-coordinate,
	to end up at the same Position
*/
class BrutePathFinder :
	public PathFinder
{
public:
	virtual void Run(Path& path, 
		             const Position& start, 
					 const Position& finish) const;

	virtual std::string Name() const;
};

