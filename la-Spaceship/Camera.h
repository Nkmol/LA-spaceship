#pragma once
#include "Matrix.h"

class Camera
{
private:
	Matrix<double, 4, 1> _eye, _lookat, _up;

public:
	Camera(const Matrix<double, 4, 1>& eye, const Matrix<double, 4, 1>& lookat, const Matrix<double, 4, 1>& up);
	Matrix<double, 4, 4> ToMatrix();

};

