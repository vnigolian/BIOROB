#include "RoomBot.hh"

RoomBot::RoomBot(int Ax, int Ay, int Az, int Bx, int By, int Bz, OBJModel* p_h1, OBJModel* p_h2) :
	_halfModuleA(Ax, Ay, Az, p_h1, p_h2), _halfModuleB(Bx, By, Bz, p_h1, p_h2) {}


RoomBot::RoomBot(Position A, Position B, OBJModel* p_h1, OBJModel* p_h2) :
	_halfModuleA(A, p_h1, p_h2), _halfModuleB(B, p_h1, p_h2) {}


void RoomBot::Draw(const glm::mat4& VP) const
{
	_halfModuleA.Draw(VP);
	_halfModuleB.Draw(VP);
}


Position RoomBot::PositionA()const
{
	return _halfModuleA.getPosition();
}

Position RoomBot::PositionB()const
{
	return _halfModuleB.getPosition();
}
