#pragma once
#include <iostream>

class Vector3d
{
public:
	Vector3d(double x, double y, double z);

	Vector3d operator*(double factor) const;
	Vector3d operator+(Vector3d& other) const;
	Vector3d operator-(Vector3d& other) const;

	double GetX() const;
	double GetY() const;
	double GetZ() const;

	friend std::ostream& operator<<(std::ostream& cout, Vector3d& vector);
private:
	double _x, _y, _z;
};

