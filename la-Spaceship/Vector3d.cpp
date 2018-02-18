#include "Vector3d.h"


Vector3d::Vector3d(double _x, double _y, double _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vector3d Vector3d::operator*(double factor)
{
	return Vector3d{ x * factor, y * factor, z * factor };
}

Vector3d Vector3d::operator+(Vector3d & other)
{
	return Vector3d{ x * other.x, y * other.y, z * other.z };
}

Vector3d Vector3d::operator-(Vector3d & other)
{
	return Vector3d{ x - other.x, y - other.y, z - other.z };
}

double Vector3d::GetX() const
{
	return this->x;
}

double Vector3d::GetY() const
{
	return this->y;
}

double Vector3d::GetZ() const
{
	return this->z;
}

std::ostream & operator<<(std::ostream & cout, Vector3d & vector)
{
	return cout << "[" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << "]";
}
