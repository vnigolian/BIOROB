#include "DirectPathFinder.hh"

void DirectPathFinder::run(Path& path, const Position& start, const Position& finish) const
{
	Position curPos = start;

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

	
	while (curPos != finish)
	{
		unsigned int min = INT_MAX;
		unsigned int minIndex = 0;
		int curDistance = min;

		for (unsigned int i(0); i < 6; i++)
		{
			curDistance = (curPos + surroundings[i]).distanceTo(finish);
			if ( curDistance < min)
			{
				min = curDistance;
				minIndex = i;
			}
		}
		curPos += surroundings[minIndex];

		path.push_back(curPos);
	}
}

std::string DirectPathFinder::name() const
{
	return "DirectPathFinder";
}

