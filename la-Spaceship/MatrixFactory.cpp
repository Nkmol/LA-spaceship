#include "MatrixFactory.h"
#include <SDL_stdinc.h>
#include <iostream>

Matrix<double, 4, 4> MatrixFactory::CreateScaleMatrix(double x_scale, double y_scale, double z_scale) const
{
	return
	{
		{ x_scale, 0, 0, 0 },
		{ 0, y_scale, 0, 0 },
		{ 0, 0, z_scale, 0 },
		{ 0,   0,   0,   1 }
	};
}

Matrix<double, 4, 4> MatrixFactory::CreateTranslationMatrix(double x_translation, double y_translation,
	double z_translation) const
{
	return
	{
		{ 1, 0, 0, x_translation },
		{ 0, 1, 0, y_translation },
		{ 0, 0, 1, z_translation },
		{ 0, 0, 0, 1 }
	};
}

Matrix<double, 4, 4> MatrixFactory::CreateRotationMatrix(double rad, const Axis axis, bool positive) const
{
	const int sin_multiplier = 1; // (positive ? 1 : -1);

	std::cout << sin_multiplier << std::endl;
	if (axis == X)
	{
		return
		{
			{ 1, 0, 0, 0 },
			{ 0, cos(rad), sin_multiplier * -sin(rad), 0 },
			{ 0, sin_multiplier * sin(rad), cos(rad), 0 },
			{ 0, 0, 0, 1 }
		};
	}
	else if (axis == Y)
	{
		return
		{
			{ cos(rad), 0, sin_multiplier * -sin(rad), 0 },
			{ 0, 1, 0, 0 },
			{ sin_multiplier * sin(rad), 0, cos(rad), 0 },
			{ 0, 0, 0, 1 }
		};
	}
	else if (axis == Z)
	{
		return
		{
			{ cos(rad), sin_multiplier * -sin(rad), 0, 0 },
			{ sin_multiplier * sin(rad), cos(rad), 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 }
		};
	}
	else
	{
		return CreateIdentityMatrix();
	}
}

Matrix<double, 4, 4> MatrixFactory::CreateIdentityMatrix() const
{
	return
	{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
}

double MatrixFactory::AngleToRadian(double angle_percentage) const
{
	return (angle_percentage / 180.0) * ((double)M_PI);
}
