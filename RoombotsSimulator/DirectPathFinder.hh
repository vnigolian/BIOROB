#pragma once
#include "PathFinder.hh"


class DirectPathFinder :
	public PathFinder
{
public:
	virtual void run(Path& path, const Position& start, const Position& finish) const;
	virtual std::string name() const;
};

