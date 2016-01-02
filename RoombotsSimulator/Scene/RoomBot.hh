#pragma once

#include "HalfModule.hh"

/**
   The Roombot class is a simple class that encapsulates two halfModules.
   It is mainly an interface class between the HalfModules and other parts
   of the software
*/

class RoomBot
{
private:
	HalfModule d_halfModuleA;
	HalfModule d_halfModuleB;

public:
	/*Returns the position of the middle between the two HalfModules*/
	glm::vec3 MiddlePosition() const
	{
		return (d_halfModuleA.GetPosition().ToGLM() + d_halfModuleB.GetPosition().ToGLM()) / 2.0f;
	}

	RoomBot(int Ax, 
		    int Ay, 
			int Az, 
			int Bx, 
			int By, 
			int Bz, 
			OBJModel* p_h1, 
			OBJModel* p_h2, 
			OBJModel* p_circle);

	RoomBot(Position A, 
		    Position B, 
			OBJModel* p_h1, 
			OBJModel* p_h2, 
			OBJModel* p_circle);

	void Draw(const glm::mat4& VP) const;

	Position PositionA()const;
	Position PositionB()const;

};