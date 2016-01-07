/**
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once
#include "common.hh"
#include "Position.hh"

typedef std::vector<Position> Path;

/**
	This class represents a path-finding algorithm.
	It is abstract, as we can design a lot of different pathi-finding algorithm, 
	and all must implement the 'run' method described below.

	The Path represents a series of successive Positions a Roombot Module must 
	pass through to get to its final position
*/
class PathFinder
{
public:
	/**	
		Creates a Path, a succession of Position from a Position to another.
		It uses an external Path and fills it
		\arg \c path A reference to the Path to fill
		\arg \c start The starting Position of the Path
		\arg \c finish The finishing Position of the Path
	*/
	virtual void Run(Path& path, 
		             const Position& start, 
					 const Position& finish) const = 0;

	/**
		This method simply returns the name of the path-finding algorithm 
	*/
	virtual std::string Name() const = 0;
};

