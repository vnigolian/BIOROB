#include "RoomBot.hh"

void RoomBot::Init(int Ax, int Ay, int Az, int Bx, int By, int Bz)
{
	_halfModuleA.Init(Ax, Ay, Az);
	_halfModuleB.Init(Bx, By, Bz);
}

void RoomBot::Draw(const glm::mat4& VP) const
{
	_halfModuleA.Draw(VP);
	_halfModuleB.Draw(VP);
}