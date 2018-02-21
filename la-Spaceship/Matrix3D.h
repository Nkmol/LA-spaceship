#pragma once

#include "Matrix.h"

// A specific implementation of the Matrix

template <typename T, unsigned int cols>
class Matrix3D : public Matrix<T, 4, cols> {
public:
	using Matrix<T, 4, cols>::Matrix;

	T Dot(const Matrix3D<T, cols>& ofMatrix) const;
};

template <typename T, unsigned int cols>
T Matrix3D<T, cols>::Dot(const Matrix3D<T, cols>& ofMatrix) const
{
	T result {};

	// Ignore the last "w" row
	for (unsigned int row = 0; row < 4 - 1; row++)
	{
		for(unsigned int col = 0; col < cols; col++) {
			result += Matrix<T, 4, cols>::Getval(row, col) * ofMatrix.Getval(row, col);
		}
	}

	return result;
}
