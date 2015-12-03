#pragma once

#include "HalfModule.hh"


class RoomBot
{
private:
	HalfModule _halfModuleA;
	HalfModule _halfModuleB;

public:
	glm::vec3 Position() const
	{
		return (_halfModuleA.Position() + _halfModuleB.Position()) / 2.0f;
	}

	void Init(int Ax, int Ay, int Az, int Bx, int By, int Bz, OBJModel* p_h1, OBJModel* p_h2);
	void Draw(const glm::mat4& VP) const;
	glm::vec3 PositionA()const;
	glm::vec3 PositionB()const;

};