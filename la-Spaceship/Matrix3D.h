#pragma once

#include "Matrix.h"
#include <math.h>       /* sqrt */

// A specific implementation of the Matrix

#define MTXTMP3D template <typename T, unsigned int cols>

MTXTMP3D
class Matrix3D : public Matrix<T, 4, cols> {
public:
	typedef Matrix<T, 4, cols> Base;
	using Base::Matrix;

	T Dot(const Matrix3D<T, cols>& ofMatrix) const;
	T Length() const;
	Matrix3D<T, cols> Normalize() const;
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

// Only for Vector (Matrix1D) length
MTXTMP3D
T Matrix3D<T, cols>::Length() const
{
	// TODO Errror when cols != 1 ? << Or support for N matrixes => { L23, L34, L5 }
	T result {};

	for(unsigned int col = 0; col < cols; col++) {
		// Ignore the last "w" row
		for (unsigned int row = 0; row < 4 - 1; row++) {
			result += Base::Getval(row, col) * Base::Getval(row, col);
		}
	}

	result = sqrt(result);
	return result;
}

MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::Normalize() const
{
	// TODO Errror when cols <= 1 ?
	Matrix3D<T, cols> result {};

	// Ignore the last "w" row
	for(unsigned int col = 0; col < cols; col++) {
		auto r = Base::Getcol(col);

		// quick-fix for convert
		Matrix3D<double, 1> vector ( 
			{ 
				{r[0]},
				{r[1]},
				{r[2]},
				{r[3]} // or 1?
			} 
		);
		auto length = vector.Length();

		for (unsigned int row = 0; row < 4 - 1; row++) {
			result.Setval(row, col, vector.Getval(row, col) / length);
		}
	}

	return result;
}

MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::Cross(const Matrix3D<T, cols>& ofMatrix) const
{
	// TODO Errror when cols > 1 ?

	// TODO functionality equals to `this * ofMatrix` ?
	return Matrix3D<T, cols> (
		{
			{ Base::Getval(1, 0) * ofMatrix.Getval(2, 0) - Base::Getval(2, 0) * ofMatrix.Getval(1, 0) }, // ay * bz - az * by
			{ Base::Getval(2, 0) * ofMatrix.Getval(0, 0) - Base::Getval(0, 0) * ofMatrix.Getval(2, 0) }, // az * bx - ax * bz
			{ Base::Getval(0, 0) * ofMatrix.Getval(1, 0) - Base::Getval(1, 0) * ofMatrix.Getval(0, 0) }, // ax * by - ay * bx
			{ 1 }																						 // default value 1 for "w", so it indicates a non-scalar matrix
		}	
	);
}

