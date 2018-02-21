#pragma once
#include "MatrixFactory.h"
#include <vector>

class MatrixHelper
{
public:
	Matrix<double, 4, 4> Rotate(double angle_percentage, Matrix<double, 4, 4> matrix, std::vector<double> edge_begin, std::vector<double> edge_end);
};

