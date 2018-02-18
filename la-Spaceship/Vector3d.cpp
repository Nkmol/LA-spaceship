#include "Vector3d.h"


Vector3d::Vector3d(const double x, const double y, const double z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3d Vector3d::operator*(const double factor) const
{
	return Vector3d{ _x * factor, _y * factor, _z * factor };
}

Vector3d Vector3d::operator+(Vector3d & other) const
{
	return Vector3d{ _x * other._x, _y * other._y, _z * other._z };
}

Vector3d Vector3d::operator-(Vector3d & other) const
{
	return Vector3d{ _x - other._x, _y - other._y, _z - other._z };
}

double Vector3d::GetX() const
{
	return _x;
}

double Vector3d::GetY() const
{
	return _y;
}

double Vector3d::GetZ() const
{
	return _z;
}

std::ostream & operator<<(std::ostream & cout, Vector3d & vector)
{
	return cout << "[" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << "]";
}
