#pragma once

#include "Matrix.h"

// A specific implementation of the Matrix

#define MTXTMP3D template <typename T, unsigned int cols>

MTXTMP3D
class Matrix3D : public Matrix<T, 4, cols> {
public:
	typedef Matrix<T, 4, cols> Base;
	using Base::Matrix;

	T Dot(const Matrix3D<T, cols>& ofMatrix) const;
	Matrix3D<T, cols> Cross(const Matrix3D<T, cols>& ofMatrix) const;
};

MTXTMP3D
T Matrix3D<T, cols>::Dot(const Matrix3D<T, cols>& ofMatrix) const
{
	T result {};

	// Ignore the last "w" row
	for (unsigned int row = 0; row < 4 - 1; row++)
	{
		for(unsigned int col = 0; col < cols; col++) {
			result += Base::Getval(row, col) * ofMatrix.Getval(row, col);
		}
	}

	return result;
}

MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::Cross(const Matrix3D<T, cols>& ofMatrix) const
{
	// TODO Errror when cols > 1 ?

	auto value = Base::Getval(0, 0);

	return Matrix3D<T, cols> (
		{
			{ Base::Getval(1, 0) * ofMatrix.Getval(2, 0) - Base::Getval(2, 0) * ofMatrix.Getval(1, 0) }, // ay * bz - az * by
			{ Base::Getval(2, 0) * ofMatrix.Getval(0, 0) - Base::Getval(0, 0) * ofMatrix.Getval(2, 0) }, // az * bx - ax * bz
			{ Base::Getval(0, 0) * ofMatrix.Getval(1, 0) - Base::Getval(1, 0) * ofMatrix.Getval(0, 0) }, // ax * by - ay * bx
			{ 1 }																						 // default value 1 for "w", so it indicates a non-scalar matrix
		}	
	);
}

