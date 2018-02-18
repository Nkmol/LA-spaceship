#pragma once
#include "Vector3d.h"

class Vector4d : public Vector3d
{
public:
	Vector4d(double x, double y, double z, double w);
	Vector4d(const Vector3d& vector3D);

	Vector4d operator*(const double factor) const;

	double GetW() const;

private:
	double _w;
};

