#include "Vector2d.h"

Vector2d::Vector2d(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
}

Vector2d Vector2d::operator*(double factor)
{
	return Vector2d{ x * factor, y * factor };
}

Vector2d Vector2d::operator+(Vector2d & other)
{
	return Vector2d{ x + other.x, y + other.y };
}

Vector2d Vector2d::operator-(Vector2d & other)
{
	return Vector2d{ x - other.x, y - other.y };
}

double Vector2d::GetX() const
{
	return this->x;
}

double Vector2d::GetY() const
{
	return this->y;
}

std::ostream & operator<<(std::ostream & cout, Vector2d & vector)
{
	return cout << "[" << vector.GetX() << ", " << vector.GetY() << "]";
}
