#pragma once
#include <iostream>

class Vector3d
{
public:
	Vector3d(double _x, double _y, double _z);
	Vector3d operator*(double factor);
	Vector3d operator+(Vector3d& other);
	Vector3d operator-(Vector3d& other);
	double GetX() const;
	double GetY() const;
	double GetZ() const;
	friend std::ostream& operator<<(std::ostream& cout, Vector3d& vector);
private:
	double x;
	double y;
	double z;
};

