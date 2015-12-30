#pragma once

#include "OBJModel.hh"
#include "../Position.hh"


class HalfModule
{
private:
	//Those are the relative coordinates within the Structure
	Position _position;

	OBJModel* _hemisphere1;
	OBJModel* _hemisphere2;
	OBJModel* _circle;

public:

	HalfModule(int, int, int, OBJModel* p_h1, OBJModel* p_h2);
	HalfModule(Position position, OBJModel* p_h1, OBJModel* p_h2);

	//void Init(int, int, int, OBJModel* p_h1, OBJModel* p_h2);
	void Draw(const glm::mat4& VP) const;
	//void Move(int x, int y, int z);

	Position getPosition() const;

	void setPosition(const Position& position);

};