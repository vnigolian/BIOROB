#pragma once

#include "OBJModel.hh"

#define MODULE_SIZE 0.12f

class HalfModule
{
private:
	int _x;
	int _y;
	int _z;

	OBJModel _hemisphere1;
	OBJModel _hemisphere2;

public:
	//HalfModule();
	//HalfModule(int x, int y, int z);
	void Init(int, int, int);
	void Draw(const glm::mat4& VP);

	glm::vec3 Position(); 

};