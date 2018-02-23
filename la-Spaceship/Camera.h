#pragma once
#include "Matrix3D.h"

class Camera
{
private:
	Matrix3D<double, 1> _eye, _lookat, _up;

public:
	Camera(const Matrix3D<double, 1>& eye, const Matrix3D<double, 1>& lookat, const Matrix3D<double, 1>& up);

};

