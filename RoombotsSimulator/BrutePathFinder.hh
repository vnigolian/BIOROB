#pragma once
#include "PathFinder.hh"
class BrutePathFinder :
	public PathFinder
{
public:
	static void run(Path& path, const Position& start, const Position& finish);

};

