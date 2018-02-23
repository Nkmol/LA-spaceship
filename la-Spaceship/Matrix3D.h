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
	T Length() const;
	Matrix3D<T, cols> Normalize() const;
	Matrix3D<T, cols> Cross(const Matrix3D<T, cols>& ofMatrix) const;
	
	// TODO Should be a way to reuse the base operators, as they all use the same underlying datatype of "myval"
	// TODO Best with exposing through inheritance, second best is proxy to Base
	Matrix3D<T, cols> operator-(const Matrix3D<T, cols>& operand) const;
	Matrix3D<T, cols> operator+(const Matrix3D<T, cols>& operand) const;
	Matrix3D<T, cols> operator-() const;
	Matrix3D<T, cols> operator*(const T operand) const;
	template <unsigned int opcols>
	Matrix3D<T, cols> operator*(const Matrix3D<T, cols>& operand) const;
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

MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::operator-(const Matrix3D<T, cols>& operand) const
{
	return (*this) + (-operand);
}

MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::operator+(const Matrix3D<T, cols>& operand) const
{
	Matrix3D<T, cols> ans {};
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < cols; j++)
			ans.myVal[i][j] = Base::myVal[i][j] + operand.myVal[i][j];
	return ans;
}

/* Negation */
MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::operator-() const
{
	return (*this) * static_cast<T>(-1);
}

/* Scalar multiplication */
MTXTMP3D
Matrix3D<T, cols> Matrix3D<T, cols>::operator*(const T operand) const
{
	Matrix3D<T, cols> ans {};
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < cols; j++)
			ans.myVal[i][j] = Base::myVal[i][j] * operand;
	return ans;
}

/* Matrix multiplication */
MTXTMP3D
template <unsigned int opcols>
Matrix3D<T, cols> Matrix3D<T, cols>::operator*(const Matrix3D<T, cols>& operand) const
{
	Matrix3D<T, cols> ans {};
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < opcols; j++)
		{
			for (unsigned int k = 0; k < cols; k++)
				ans.Setval(i, j, ans.Getval(i, j) + this->Getval(i, k) * operand.Getval(k, j));
		}
	}
	return ans;
}
