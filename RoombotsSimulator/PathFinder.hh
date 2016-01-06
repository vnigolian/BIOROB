/*
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
		This method takes a Path, a starting position and a finish position as arguments 
		and fills the path with a series of Positions going from start to finish
	*/
	virtual void Run(Path& path, 
		             const Position& start, 
					 const Position& finish) const = 0;

	/**
		This method simply returns the name of the path-finding algorithm 
	*/
	virtual std::string Name() const = 0;
};

