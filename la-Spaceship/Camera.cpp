#include "Camera.h"
#include "MatrixHelper.h"
#include <iostream>

Camera::Camera(const Matrix<double, 4, 1>& eye, const Matrix<double, 4, 1>& lookat, const Matrix<double, 4, 1>& up) : _eye{eye}, _lookat(lookat), _up{up}
{
}

Matrix<double, 4, 4> Camera::CalculateMatrix()
{
	MatrixHelper helper;

	// Setup vectors for matrix
	auto z = helper.Normalize(_eye - _lookat);
	auto y = helper.Normalize(_up);
	auto x = helper.Normalize(helper.Cross(y, z));
	y = helper.Normalize(helper.Cross(z, x));

	Matrix<double, 4, 4> camera(
	{
		{ x.Getval(0, 0), x.Getval(1, 0), x.Getval(2, 0), -helper.Dot(x, _eye) },
		{ y.Getval(0, 0), y.Getval(1, 0), y.Getval(2, 0), -helper.Dot(y, _eye) },
		{ z.Getval(0, 0), z.Getval(1, 0), z.Getval(2, 0), -helper.Dot(z, _eye) },
		{ 0, 0, 0, 1 },
	}
	);


	return camera;
}
