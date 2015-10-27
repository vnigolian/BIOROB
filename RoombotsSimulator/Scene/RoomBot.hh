#pragma once

#include "HalfModule.hh"


class RoomBot
{
private:
	HalfModule _halfModuleA;
	HalfModule _halfModuleB;

public:
	glm::vec3 Position()
	{
		return (_halfModuleA.Position() + _halfModuleB.Position()) / 2.0f;
	}

};