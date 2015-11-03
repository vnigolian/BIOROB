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

	void Init(int Ax, int Ay, int Az, int Bx, int By, int Bz);
	void Draw(const glm::mat4& VP) const;
	//void Move(int x)
};