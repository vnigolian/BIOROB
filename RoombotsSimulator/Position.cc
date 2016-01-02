#include "Position.hh"


Position::Position() : d_x(0),d_y(0),d_z(0) {}

Position::Position(int x, int y, int z): d_x(x), d_y(y), d_z(z) {}

Position::Position(Position* other): d_x(other->d_x),d_y(other->d_y), d_z(other->d_z) {}

Position::Position(glm::vec3 other) : d_x((int)(other.x / MODULE_SIZE)), d_y((int)(other.y / MODULE_SIZE)), d_z((int)(other.z / MODULE_SIZE)) {}

Position Position::operator+(Position other) const
{
	return Position(this->d_x + other.d_x, this->d_y + other.d_y, this->d_z + other.d_z);
}

Position Position::operator-(Position other) const
{
	return new Position(this->d_x - other.d_x, this->d_y - other.d_y, this->d_z - other.d_z);
}


Position Position::operator*(int factor) const
{
	return Position(this->d_x * factor, this->d_y * factor, this->d_z * factor);
}

void Position::operator+=(Position other)
{
	d_x += other.d_x;
	d_y += other.d_y;
	d_z += other.d_z;
}

void Position::operator-=(Position other)
{
	d_x -= other.d_x;
	d_y -= other.d_y;
	d_z -= other.d_z;
}

void Position::operator*=(int factor)
{
	d_x *= factor;
	d_y *= factor;
	d_z *= factor;
}

bool Position::operator==(Position other) const
{
	return (this->d_x == other.d_x) && (this->d_y && other.d_y) && (this->d_z == other.d_z);
}

bool Position::operator!=(Position other) const 
{ 
	return !(*this == other); 
}


int Position::distanceTo(Position other) const
{
	return (int)(abs(this->d_x - other.d_x) + abs(this->d_y - other.d_y) + abs(this->d_z - other.d_z));
}

void Position::Print() const
{
	std::cout << "(" << d_x << "," << d_y << "," << d_z << ")" << std::endl;
}

glm::vec3 Position::ToGLM() const
{
	return glm::vec3(d_x, d_y, d_z);
}


int Position::x() const
{
	return d_x;
}

int Position::y() const
{
	return d_y;
}

int Position::z() const
{
	return d_z;
}
