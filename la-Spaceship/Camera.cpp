s#include "Camera.h"
#include "MatrixHelper.h"

Camera::Camera(const Matrix<double, 4, 1>& eye, const Matrix<double, 4, 1>& lookat,
               const Matrix<double, 4, 1>& up) : _eye{eye}, _lookat(lookat), _up{up}
{
}

void Camera::SetLookAt(const Matrix<double, 4, 1>& lookAt)
{
	_lookat = lookAt;
}

const Matrix<double, 4, 1>& Camera::GetLookAt() const
{
	return _lookat;
}

void Camera::SetEye(const Matrix<double, 4, 1>& eye)
{
	_eye = eye;
}

const Matrix<double, 4, 1>& Camera::GetEye() const
{
	return _eye;
}

Matrix<double, 4, 4> Camera::CalculateMatrix() const
{
	MatrixHelper helper;

	// Setup vectors for matrix
	auto z = helper.Normalize(_eye - _lookat);
	auto y = helper.Normalize(_up);
	auto x = helper.Normalize(helper.Cross(y, z));
	y = helper.Normalize(helper.Cross(z, x));

	Matrix<double, 4, 4> camera(
		{
			{x.GetVal(0, 0), x.GetVal(1, 0), x.GetVal(2, 0), -helper.Dot(x, _eye)},
			{y.GetVal(0, 0), y.GetVal(1, 0), y.GetVal(2, 0), -helper.Dot(y, _eye)},
			{z.GetVal(0, 0), z.GetVal(1, 0), z.GetVal(2, 0), -helper.Dot(z, _eye)},
			{0, 0, 0, 1},
		}
	);

	return camera;
}
