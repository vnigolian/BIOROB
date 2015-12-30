#include "DirectPathFinder.hh"

Path DirectPathFinder::run(Position initPos, Position finalPos)
{
	Position curPos = initPos;
	Path path;

	/*surroundings in the form :
	left
	right
	front
	back
	up
	down*/

	Position surroundings[6] =
	{
		Position(-1, 0, 0),
		Position(1, 0, 0),
		Position(0, 0, -1),
		Position(0, 0, 1),
		Position(0, 1, 0),
		Position(0, -1, 0)
	};

	unsigned int min = INT_MAX;
	unsigned int minIndex = 0;

	while (curPos != finalPos)
	{
		min = INT_MAX;
		int curDistance = min;
		for (unsigned int i(0); i < 6; i++)
		{
			
		}
	}

	return path;
}

