#include "MatrixHelper.h"

double MatrixHelper::Dot(const Vector3D& one, const Vector3D& two) const
{
	double result {};

	// Ignore the last "w" row
	for (unsigned int row = 0; row < 4 - 1; row++)
	{
		for(unsigned int col = 0; col < 1; col++) {
			result += one.Getval(row, col) * two.Getval(row, col);
		}
	}

	return result;
}

double MatrixHelper::Length(const Vector3D& one) const
{
	double result {};

	for(unsigned int col = 0; col < 1; col++) {
		// Ignore the last "w" row
		for (unsigned int row = 0; row < 4 - 1; row++) {
			result += one.Getval(row, col) * one.Getval(row, col);
		}
	}

	result = sqrt(result);
	return result;
}

MatrixHelper::Vector3D MatrixHelper::Normalize(const Vector3D& one) const
{
	// TODO Errror when cols <= 1 ?
	Vector3D result {};

	// Ignore the last "w" row
	for(unsigned int col = 0; col < 1; col++) {
		auto r = one.Getcol(col);

		// quick-fix for convert
		Vector3D vector ( 
			{ 
				{r[0]},
				{r[1]},
				{r[2]},
				{r[3]} // or 1?
			} 
		);
		const auto length = Length(vector);

		for (unsigned int row = 0; row < 4 - 1; row++) {
			const auto normalized = vector.Getval(row, col) / length;
			
			result.Setval(row, col, normalized);
		}
	}

	return result;
}

MatrixHelper::Vector3D MatrixHelper::Cross(const Vector3D& one, const Vector3D& two) const
{
	// TODO Errror when cols > 1 ?

	// TODO functionality equals to `this * ofMatrix` ?
	return Vector3D (
		{
			{ one.Getval(1, 0) * two.Getval(2, 0) - one.Getval(2, 0) * two.Getval(1, 0) }, // ay * bz - az * by
			{ one.Getval(2, 0) * two.Getval(0, 0) - one.Getval(0, 0) * two.Getval(2, 0) }, // az * bx - ax * bz
			{ one.Getval(0, 0) * two.Getval(1, 0) - one.Getval(1, 0) * two.Getval(0, 0) }, // ax * by - ay * bx
			{ 1 }																						 // default value 1 for "w", so it indicates a non-scalar matrix
		}	
	);
}