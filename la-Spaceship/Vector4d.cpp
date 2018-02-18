#include "Vector4d.h"


Vector4d::Vector4d(const double x, const double y, const double z, const double w) : Vector3d(x, y, z), _w{w} 
{
}

// Implicit 3D static point to 4D vector that can be translated
/// https://gamedev.stackexchange.com/questions/14115/do-i-need-the-w-component-in-my-vector-class
Vector4d::Vector4d(const Vector3d& vector3D) : Vector3d(vector3D), _w{1}
{
}

Vector4d Vector4d::operator*(const double factor) const
{
	return Vector4d{ GetX() * factor, GetY() * factor, GetZ() * factor, GetW() * factor};
}

double Vector4d::GetW() const
{
	return _w;
}

std::ostream & operator<<(std::ostream & cout, Vector4d & vector)
{
	return cout << "[" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ", " << vector.GetW() << "]";
}
