#pragma once
#include "MatrixFactory.h"
#include <vector>

class MatrixHelper
{
public:
	Matrix<double, 4, 4> Rotate(double angle_percentage, Matrix<double, 4, 4> matrix, std::vector<double> edge_begin, std::vector<double> edge_end);
	
	typedef double ValueType;
	typedef Matrix<ValueType, 4, 1> Vector3D;
	double Dot(const Vector3D& one, const Vector3D& two) const;
	double Length(const Vector3D& one) const;
	Vector3D Normalize(const Vector3D & one) const;
	Vector3D Cross(const Vector3D & one, const Vector3D & two) const;
};

