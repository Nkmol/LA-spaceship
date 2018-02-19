#pragma once
#include "MatrixFactory.h"

class MatrixHelper
{
public:
	Matrix<double, 4, 4> Rotate(double angle_percentage, Matrix<double, 4, 4> matrix, double x, double y, double z);
};

