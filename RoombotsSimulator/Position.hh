/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#pragma once
#include "common.hh"

/**
   This class is a simple triplet of integers that represent a discrete Position.
   It allows easier handling of grid-bound objects.
   The grid is also Roombot-sized.
   It has basic operators and methods, as expected from such object
*/
class Position
{
	//Those are pretty self-explanatory
	int d_x;
	int d_y;
	int d_z;

public:
	/*This constructor creates a new Position at (0,0,0)*/
	Position();

	/*This constructor creates a new Position at (x,y,z)*/
	Position(int x, 
		     int y, 
			 int z);

	/*Copy constructor*/
	Position(Position*);

	/*This constructor converts a 'glm::vec3' into a Position that
	is at the closest spot on the grid from the 'glm::vec3' passed as argument*/
	Position(glm::vec3);
	
	Position operator+(Position other) const;
	Position operator-(Position other) const;
	Position operator*(int factor) const;
	void operator+=(Position other);
	void operator-=(Position other);
	void operator*=(int factor);
	bool operator==(Position other) const;
	bool operator!=(Position other) const;

	/*Sums up the difference between all three coordinates of 'this' and 'other'*/
	int distanceTo(Position other) const;

	/*Prints out the Position as (x,y,z)*/
	void Print() const;

	/*Returns a 'glm::vec3' equivalent to the Position*/
	glm::vec3 ToGLM() const;

	int x() const;
	int y() const;
	int z() const;
};

