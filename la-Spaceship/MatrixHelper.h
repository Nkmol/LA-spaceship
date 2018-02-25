#pragma once
#include "MatrixFactory.h"
#include <vector>

class MatrixHelper
{
public:

	template<int width>
	Matrix<double, 4, width> Rotate(double angle_percentage, Axis axis, Matrix<double, 4, width> matrix, std::vector<double> edge_begin, std::vector<double> edge_end)
	{
		MatrixFactory factory;
		int height = 4;


		const double x_translate = -edge_begin[0];
		const double y_translate = -edge_begin[1];
		const double z_translate = -edge_begin[2];

		const double x = edge_end[0];
		const double y = edge_end[1];
		const double z = edge_end[2];

		const auto translate = factory.CreateTranslationMatrix(x_translate, y_translate, z_translate);
		const auto revert = factory.CreateTranslationMatrix(-x_translate, -y_translate, -z_translate);

		const double rad = factory.AngleToRadian(angle_percentage);

		const double t1 = atan2(z, x); // Rad to rotate z edge to 0
		const double t2 = atan2(y, sqrt(pow(x, 2) + pow(z, 2))); // Rad to rotate y edge to 0

		const auto z_rot = factory.CreateRotationMatrix(t1, Y, true); // Rotate Z edge to 0
		const auto y_rot = factory.CreateRotationMatrix(t2, Z, true); // Rotate Y edge to 0
		const auto x_rot = factory.CreateRotationMatrix(rad, X, true); // Rotate around the given edge
		const auto y_ret = factory.CreateRotationMatrix(-t2, Y, false); // Rotate Y edge back
		const auto z_ret = factory.CreateRotationMatrix(-t1, Z, false); // Rotate Z edge back

		return (revert * (factory.CreateRotationMatrix(rad, axis) * translate)) * matrix;

		auto result = (revert * (z_ret * (y_ret * (x_rot * (y_rot * (z_rot * translate)))))) * matrix;


		// When the matrix is rotated, some values may be very close to zero (due to cos / sin)
		// To fix this the value is rounded down when there are a lot decimals.
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				result.SetVal(y, x, floor(result.GetVal(y, x) * 100) / 100);
			}
		}

		return result;
	}

	template<int width>
	Matrix<double, 4, 4> Rotate(double angle_percentage, Matrix<double, 4, width> matrix, std::vector<double> edge_begin, std::vector<double> edge_end)
	{
		MatrixFactory factory;
		int height = 4;


		const double x_translate = -edge_begin[0];
		const double y_translate = -edge_begin[1];
		const double z_translate = -edge_begin[2];

		const double x = edge_end[0];
		const double y = edge_end[1];
		const double z = edge_end[2];

		const auto translate = factory.CreateTranslationMatrix(x_translate, y_translate, z_translate);
		const auto revert = factory.CreateTranslationMatrix(-x_translate, -y_translate, -z_translate);

		const double rad = factory.AngleToRadian(angle_percentage);

		const double t1 = atan2(z, x); // Rad to rotate z edge to 0
		const double t2 = atan2(y, sqrt(pow(x, 2) + pow(z, 2))); // Rad to rotate y edge to 0

		const auto y_rot = factory.CreateRotationMatrix(t1, Y, true); // Rotate Z edge to 0
		const auto z_rot = factory.CreateRotationMatrix(t2, Z, true); // Rotate Y edge to 0
		const auto x_rot = factory.CreateRotationMatrix(rad, X, true); // Rotate around the given edge
		const auto z_ret = factory.CreateRotationMatrix(-t2, Z, false); // Rotate Y edge back
		const auto y_ret = factory.CreateRotationMatrix(-t1, Y, false); // Rotate Z edge back

		auto result = ((y_ret * (z_ret * (x_rot * (z_rot * (y_rot))))));


		//// When the matrix is rotated, some values may be very close to zero (due to cos / sin)
		//// To fix this the value is rounded down when there are a lot decimals.
		//for (int x = 0; x < width; x++)
		//{
		//	for (int y = 0; y < height; y++)
		//	{
		//		result.SetVal(y, x, floor(result.GetVal(y, x) * 100) / 100);
		//	}
		//}

		return result;
	}

	typedef double ValueType;
	typedef Matrix<ValueType, 4, 1> Vector3D;
	double Dot(const Vector3D& one, const Vector3D& two) const;
	double Length(const Vector3D& one) const;
	Vector3D Normalize(const Vector3D & one) const;
	Vector3D Cross(const Vector3D & one, const Vector3D & two) const;
};

