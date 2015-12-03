#include "RoomBot.hh"

void RoomBot::Init(int Ax, int Ay, int Az, int Bx, int By, int Bz, OBJModel* p_h1, OBJModel* p_h2)
{
	_halfModuleA.Init(Ax, Ay, Az, p_h1, p_h2);
	_halfModuleB.Init(Bx, By, Bz, p_h1, p_h2);
}

void RoomBot::Draw(const glm::mat4& VP) const
{
	_halfModuleA.Draw(VP);
	_halfModuleB.Draw(VP);
}


glm::vec3 RoomBot::PositionA()const
{
	return _halfModuleA.Position();
}

glm::vec3 RoomBot::PositionB()const
{
	return _halfModuleB.Position();
}
