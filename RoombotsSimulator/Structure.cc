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

int max(int a, int b)
{
	if (a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int max(int a, int b, int c)
{
	return max(max(a, b), c);
}



Structure::Structure(std::string sourceFilename, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) : d_filename(sourceFilename)
{
	std::fstream in(sourceFilename);
	if (in.is_open())
	{
		std::vector<Position> positions;
		int minX = 0, minY = 0, minZ = 0;
		int maxX = 0, maxY = 0, maxZ = 0;

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
			
			maxX = max(maxX, Ax, Bx);
			maxY = max(maxY, Ay, By);
			maxZ = max(maxZ, Az, Bz);

			minX = min(minX, Ax, Bx);
			minY = min(minY, Ay, By);
			minZ = min(minZ, Az, Bz);

			positions.push_back({ Ax, Ay, Az });
			positions.push_back({ Bx, By, Bz });

			//std::cout << Ax << "," << Ay << "," << Az << "," << Bx << "," << By << ","<< Bz << std::endl;
		}
		for (size_t i = 0; i < positions.size(); i+=2)
		{
			RoomBot roomBot(positions[i].x() - minX, positions[i].y() - minY, positions[i].z() - minZ,
				positions[i + 1].x() - minX, positions[i + 1].y() - minY, positions[i + 1].z() - minZ,
						 p_h1, p_h2, p_circle);
			d_roomBots.push_back(roomBot);
		}

		d_centerOffset = MODULE_SIZE * glm::vec3(((float) maxX + 1.) / 2., ((float) maxY + 1) / 2, ((float) maxZ + 1.) / 2.);
	}
	else
	{
		std::cerr << "ERROR - couldn't open Structure file" << std::endl;
	}
	

	//std::cout << "center offset is at : " << d_centerOffset.x << " " << d_centerOffset.y << " " << d_centerOffset.z << std::endl;

	centerCube = new Cube("Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	centerCube->SetModelMatrix(glm::translate(d_centerOffset) * glm::scale(glm::mat4(1.0f), glm::vec3(0.12f)));
	
}



void Structure::Draw(const glm::mat4& VP) const
{

	for (size_t i = 0; i < d_roomBots.size(); i++)
	{
		d_roomBots[i].Draw(VP * glm::translate(-d_centerOffset));
	}
	centerCube->Draw(VP* glm::translate(-d_centerOffset));
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

