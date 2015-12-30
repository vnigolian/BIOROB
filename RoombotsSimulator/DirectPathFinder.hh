#pragma once
#include "PathFinder.hh"
class DirectPathFinder :
	public PathFinder
{
public:
	virtual Path run(Position initPos, Position finalPos) const;

};

