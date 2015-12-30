#pragma once
#include "common.hh"
#include "Position.hh"

typedef std::vector<Position> Path;

class PathFinder
{
public:
	virtual void run(Path& path, const Position& start, const Position& finish) const = 0;
};

