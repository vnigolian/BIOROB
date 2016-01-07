/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "Structure.hh"
int min(int a, int b)
{
	if (a<b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int min(int a, int b, int c)
{
	return min(min(a, b), c);
}

typedef struct
{
	int x;
	int y;
	int z;
} Triplet;

Structure::Structure(std::string sourceFilename, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) : d_filename(sourceFilename)
{
	std::fstream in(sourceFilename);
	if (in.is_open())
	{
		std::vector<Triplet> positions;
		int minX = 0, minY = 0, minZ = 0;
		std::cout << "Loading " + sourceFilename + " file" << std::endl;
		while (!in.eof())
		{
			int Ax, Ay, Az, Bx, By, Bz;
			in >> Ax;
			in >> Ay;
			in >> Az;
			in >> Bx;
			in >> By;
			in >> Bz;
			
			minX = min(minX, Ax, Bx);
			minY = min(minY, Ay, By);
			minZ = min(minZ, Az, Bz);

			positions.push_back({ Ax, Ay, Az });
			positions.push_back({ Bx, By, Bz });

			//std::cout << Ax << "," << Ay << "," << Az << "," << Bx << "," << By << ","<< Bz << std::endl;
		}
		for (size_t i = 0; i < positions.size(); i+=2)
		{
			RoomBot roomBot(positions[i].x - minX, positions[i].y - minY, positions[i].z - minZ,
				         positions[i+1].x - minX, positions[i+1].y - minY, positions[i+1].z - minZ,
						 p_h1, p_h2, p_circle);
			d_roomBots.push_back(roomBot);
		}
		
	}
	else
	{
		std::cerr << "ERROR - couldn't open Structure file" << std::endl;
	}
	SetCenterOffset();
}


void Structure::SetCenterOffset()
{
	glm::vec3 centerOffset(0.0f);
	size_t size = d_roomBots.size();

	//The center's offset is simply an average of all the Roombots relative Position
	for (size_t i = 0; i < size; i++)
	{
		glm::vec3 roomBotPosition = d_roomBots[i].MiddlePosition();
		centerOffset += (1 / (float)size) * glm::vec3(roomBotPosition.x, roomBotPosition.y, roomBotPosition.z);
	}
	d_centerOffset = MODULE_SIZE * centerOffset;// -glm::vec3(MODULE_SIZE / 2, MODULE_SIZE / 2, -MODULE_SIZE / 2);
}

void Structure::Draw(const glm::mat4& VP) const
{

	for (size_t i = 0; i < d_roomBots.size(); i++)
	{
		d_roomBots[i].Draw(VP);
	}
}


glm::vec3 Structure::CenterOffset() const
{
	return d_centerOffset;
}

std::vector<Position> Structure::RoombotsPositions() const
{
	std::vector<Position> positions;
	for (size_t i(0); i < d_roomBots.size(); i++)
	{
		positions.push_back(d_roomBots[i].PositionA());
		positions.push_back(d_roomBots[i].PositionB());
	}

	return positions;
}

