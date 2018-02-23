#include "Camera.h"

Camera::Camera(const Matrix3D<double, 1>& eye, const Matrix3D<double, 1>& lookat, const Matrix3D<double, 1>& up) : _eye{eye}, _lookat(lookat), _up{up}
{
	// Setup vectors for matrix
	auto r = eye-lookat;
	auto l  = r.Length();

	auto z = (eye-lookat).Normalize();
	auto y = up.Normalize();
	auto x = (y*z).Normalize();
	y = (z*x).Normalize();


}
