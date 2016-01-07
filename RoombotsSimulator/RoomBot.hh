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
	HalfModule d_halfModuleA; ///<The first half of the Roombot
	HalfModule d_halfModuleB; ///<The second half of the Roombot

public:
	
	/**Creates a new RoomBot
	\arg \c A The Position of the first HalfModule
	\arg \c B The Position of the second HalfModule
	\arg p_h1,p_h2_p_circle Pointers to OBJModel used to construct the two HalfModule
	*/
	RoomBot(Position A, 
		    Position B, 
			OBJModel* p_h1, 
			OBJModel* p_h2, 
			OBJModel* p_circle);

	/**Same as the first constructor but with the six \c int used to create the two necessary \c Position*/
	RoomBot(int Ax,
		int Ay,
		int Az,
		int Bx,
		int By,
		int Bz,
		OBJModel* p_h1,
		OBJModel* p_h2,
		OBJModel* p_circle);

	/**Returns the position of the middle between the two HalfModules*/
	glm::vec3 MiddlePosition() const
	{
		return (d_halfModuleA.GetPosition().ToGLM() + d_halfModuleB.GetPosition().ToGLM()) / 2.0f;
	}
	/**Draws the RoomBot*/
	void Draw(const glm::mat4& VP) const;

	/**Returns the Position of the first HalfModule*/
	Position PositionA()const;

	/**Returns the Position of the second HalfModule*/
	Position PositionB()const;

};