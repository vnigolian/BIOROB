#include "RoomBot.hh"

RoomBot::RoomBot(int Ax, int Ay, int Az, int Bx, int By, int Bz, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) :
RoomBot(Position(Ax, Ay, Az), Position(Bx, By, Bz), p_h1, p_h2, p_circle){}


RoomBot::RoomBot(Position A, Position B, OBJModel* p_h1, OBJModel* p_h2, OBJModel* p_circle) :
d_halfModuleA(A, p_h1, p_h2, p_circle), d_halfModuleB(B, p_h1, p_h2, p_circle) {}


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
