#pragma once

#include "HalfModule.hh"


class RoomBot
{
private:
	HalfModule _halfModuleA;
	HalfModule _halfModuleB;

public:
	glm::vec3 MiddlePosition() const
	{
		return (_halfModuleA.getPosition().toGLM() + _halfModuleB.getPosition().toGLM()) / 2.0f;
	}

	RoomBot(int Ax, int Ay, int Az, int Bx, int By, int Bz, OBJModel* p_h1, OBJModel* p_h2);

	void Draw(const glm::mat4& VP) const;
	Position PositionA()const;
	Position PositionB()const;

};