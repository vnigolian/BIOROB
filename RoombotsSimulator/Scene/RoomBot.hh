#pragma once

#include "OBJModel.hh"


#define MODULE_SIZE 0.12f

class RoomBot
{
private:
	OBJModel _cubeA;
	OBJModel _cubeB;
	int _x;
	int _y;
	int _z;

public:
	glm::vec3 Position()
	{
		return glm::vec3(_x, _y, _z);
	}

};