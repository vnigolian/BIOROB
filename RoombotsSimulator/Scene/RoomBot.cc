#include "RoomBot.hh"

RoomBot::RoomBot(int Ax, int Ay, int Az, int Bx, int By, int Bz, OBJModel* p_h1, OBJModel* p_h2) :
	d_halfModuleA(Ax, Ay, Az, p_h1, p_h2), d_halfModuleB(Bx, By, Bz, p_h1, p_h2) {}


RoomBot::RoomBot(Position A, Position B, OBJModel* p_h1, OBJModel* p_h2) :
	d_halfModuleA(A, p_h1, p_h2), d_halfModuleB(B, p_h1, p_h2) {}


void RoomBot::Draw(const glm::mat4& VP) const
{
	d_halfModuleA.Draw(VP);
	d_halfModuleB.Draw(VP);
}


Position RoomBot::PositionA()const
{
	return d_halfModuleA.GetPosition();
}

Position RoomBot::PositionB()const
{
	return d_halfModuleB.GetPosition();
}
