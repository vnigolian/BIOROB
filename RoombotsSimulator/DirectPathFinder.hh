#pragma once
#include "PathFinder.hh"
class DirectPathFinder :
	public PathFinder
{
public:
	static Path run(Position initPos, Position finalPos);

};

