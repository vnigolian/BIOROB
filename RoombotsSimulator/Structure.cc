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

Structure::Structure(std::string sourceFilename)
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
			RoomBot roomBot;
			roomBot.Init(positions[i].x - minX, positions[i].y - minY, positions[i].z - minZ,
				         positions[i+1].x - minX, positions[i+1].y - minY, positions[i+1].z - minZ);
			roomBots.push_back(roomBot);
		}
		
	}
	else
	{
		std::cerr << "ERROR - couldn't open Structure file" << std::endl;
	}
	SetCenterOffset();
}

Structure::Structure(Structure* other)
{
	for (size_t i = 0; i < other->roomBots.size(); i++)
	{
		roomBots.push_back(other->roomBots[i]);
	}
	_centerOffset = other->CenterOffset();
	std::cout << "copied a Structure" << std::endl;
}

void Structure::SetCenterOffset()
{
	glm::vec3 centerOffset;
	size_t size = roomBots.size();
	for (size_t i = 0; i < size; i++)
	{
		glm::vec3 roomBotPosition = roomBots[i].Position();
		centerOffset += (1 / (float)size) * glm::vec3(roomBotPosition.x, roomBotPosition.y, -roomBotPosition.z);
	}
	_centerOffset = MODULE_SIZE * centerOffset - glm::vec3(MODULE_SIZE / 2, MODULE_SIZE / 2, -MODULE_SIZE / 2);
}

void Structure::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);

	for (size_t i = 0; i < roomBots.size(); i++)
	{
		//we multiply the VP matrix by a translation to draw the modules at the right place
		roomBots[i].Draw(VP);
	}
	glDisable(GL_BLEND);
}


glm::vec3 Structure::CenterOffset() const
{
	return _centerOffset;
}

void Structure::CleanUp()
{

}

