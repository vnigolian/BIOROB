#pragma once
#include "common.hh"

class Position
{
	int _x;
	int _y;
	int _z;

public:
	Position();
	Position(int x, int y, int z);
	Position(Position*);
	Position(glm::vec3);
	
	Position operator+(Position other) const;
	Position operator-(Position other) const;
	Position operator*(int factor) const;
	void operator+=(Position other);
	void operator-=(Position other);
	void operator*=(int factor);
	bool operator==(Position other) const;
	bool operator!=(Position other) const;

	int distanceTo(Position other) const;
	void print() const;

	glm::vec3 toGLM() const;

	int x() const;
	int y() const;
	int z() const;
};

