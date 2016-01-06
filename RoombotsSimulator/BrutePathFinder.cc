/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "BrutePathFinder.hh"

void BrutePathFinder::Run(Path& path, const Position& start, const Position& finish) const
{
	path.clear();

	Position curPos = start;
	
	int xDistance = finish.x() - start.x();
	int yDistance = finish.y() - start.y();
	int zDistance = finish.z() - start.z();

	for (unsigned int i(0); i < (unsigned int)abs(zDistance); i++)
	{
		curPos = curPos + Position(0,0,1)*((zDistance > 0) - (zDistance < 0));
		path.push_back(curPos);
	}

	for (unsigned int i(0); i < (unsigned int)abs(xDistance); i++)
	{
		curPos = curPos + Position(1, 0, 0)*((xDistance > 0) - (xDistance < 0));
		path.push_back(curPos);
	}

	for (unsigned int i(0); i < (unsigned int)abs(yDistance); i++)
	{
		curPos = curPos + Position(0, 1, 0)*((yDistance > 0) - (yDistance < 0));
		path.push_back(curPos);
	}
}

std::string BrutePathFinder::Name() const
{
	return "BrutePathFinder";
}

