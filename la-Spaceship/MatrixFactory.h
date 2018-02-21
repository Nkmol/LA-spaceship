#pragma once
#include "Matrix.h"

enum Axis
{
	X,
	Y,
	Z,
	UNKNOWN
};

class MatrixFactory
{
public:
	Matrix<double, 4, 4> CreateScaleMatrix(double x_scale = 1, double y_scale = 1, double z_scale = 1) const;
	Matrix<double, 4, 4> CreateTranslationMatrix(double x_translation = 0, double y_translation = 0, double z_translation = 0) const;
	
	Matrix<double, 4, 4> CreateRotationMatrix(double rad, const Axis axis = X, bool positive = true) const;

	Matrix<double, 4, 4> CreateIdentityMatrix() const;

	double AngleToRadian(double angle_percentage) const;
};

