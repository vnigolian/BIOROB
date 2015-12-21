#pragma once

#include "OBJModel.hh"

#define MODULE_SIZE 0.12f

class HalfModule
{
private:
	//Those are the relative coordinates within the Structure
	int _x;
	int _y;
	int _z;

	OBJModel* _hemisphere1;
	OBJModel* _hemisphere2;
	OBJModel* _circle;

public:
	//HalfModule();
	//HalfModule(int x, int y, int z);
	HalfModule(int, int, int, OBJModel* p_h1, OBJModel* p_h2);
	//void Init(int, int, int, OBJModel* p_h1, OBJModel* p_h2);
	void Draw(const glm::mat4& VP) const;
	//void Move(int x, int y, int z);

	glm::vec3 Position() const;


};