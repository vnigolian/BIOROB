#include "Position.hh"


Position::Position() : _x(0),_y(0),_z(0) {}

Position::Position(int x, int y, int z): _x(x), _y(y), _z(z) {}

Position::Position(Position* other): _x(other->_x),_y(other->_y), _z(other->_z) {}

//Position::Position(glm::vec3 other) : _x(floor(other.x)), _y(floor(other.y)), _z(floor(other.z )) {}

Position::Position(glm::vec3 other) : _x((int)(other.x / MODULE_SIZE)), _y((int)(other.y / MODULE_SIZE)), _z((int)(other.z / MODULE_SIZE)) {}

Position Position::operator+(Position other) const
{
	return Position(this->_x + other._x, this->_y + other._y, this->_z + other._z);
}

Position Position::operator-(Position other) const
{
	return new Position(this->_x - other._x, this->_y - other._y, this->_z - other._z);
}


Position Position::operator*(int factor) const
{
	return Position(this->_x * factor, this->_y * factor, this->_z * factor);
}

void Position::operator+=(Position other)
{
	_x += other._x;
	_y += other._y;
	_z += other._z;
}

void Position::operator-=(Position other)
{
	_x -= other._x;
	_y -= other._y;
	_z -= other._z;
}

void Position::operator*=(int factor)
{
	_x *= factor;
	_y *= factor;
	_z *= factor;
}

bool Position::operator==(Position other) const
{
	return (this->_x == other._x) && (this->_y && other._y) && (this->_z == other._z);
}

bool Position::operator!=(Position other) const 
{ 
	return !(*this == other); 
}


int Position::distanceTo(Position other) const
{
	return (int)(abs(this->_x - other._x) + abs(this->_y - other._y) + abs(this->_z - other._z));
}

void Position::print() const
{
	std::cout << "(" << _x << "," << _y << "," << _z << ")" << std::endl;
}

glm::vec3 Position::toGLM() const
{
	return glm::vec3(_x, _y, _z);
}


int Position::x() const
{
	return _x;
}

int Position::y() const
{
	return _y;
}

int Position::z() const
{
	return _z;
}
