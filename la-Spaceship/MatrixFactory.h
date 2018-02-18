#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

enum Axis
{
	X,
	Y,
	Z
};

class MatrixFactory
{
public:
	/*Matrix3d CreateTranslationMatrix(const Vector2d& addition) const;
	Matrix2d CreateScalingMatrix(const Vector2d& scaling) const;
	Matrix2d Create2dRotationMatrix(double angle_percentage) const;
	Matrix2d Create2dNulMatrix() const;
	Matrix2d Create2dIdentityMatrix() const;
	Matrix CreateTranslationMatrix(const Vector3d& addition) const;
	Matrix3d CreateScalingMatrix(const Vector3d& scaling) const;
	Matrix3d CreateRotationMatrix(double angle_percentage, const Vector3d& edge_begin, const Vector3d& edge_end) const;
	Matrix3d CreateRotationMatrix(double angle_percentage, Axis axis) const;
	Matrix3d CreateNulMatrix() const;
	Matrix3d CreateIdentityMatrix() const;*/
private:
	double AngleToRadian(double angle_percentage) const;
};

