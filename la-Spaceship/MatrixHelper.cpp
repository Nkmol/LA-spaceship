#include "MatrixHelper.h"

Matrix<double, 4, 4> MatrixHelper::Rotate(double angle_percentage, Matrix<double, 4, 4> matrix,
                                          std::vector<double> edge_begin, std::vector<double> edge_end) const
{
	MatrixFactory factory;
	int width = 4;
	int height = 4;


	const double x_translate = -edge_begin[0];
	const double y_translate = -edge_begin[1];
	const double z_translate = -edge_begin[2];

	const double x = edge_end[0] + x_translate;
	const double y = edge_end[1] + y_translate;
	const double z = edge_end[2] + z_translate;

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

	auto result = revert * (z_ret * (y_ret * (x_rot * (y_rot * (z_rot * translate))))) * matrix;


	// When the matrix is rotated, some values may be very close to zero (due to cos / sin)
	// To fix this the value is rounded down when there are a lot decimals.
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			result.SetVal(y, x, floor(result.GetVal(y, x) * 1000000) / 1000000);
		}
	}

	return result;
}

double MatrixHelper::Dot(const Vector3D& one, const Vector3D& two) const
{
	double result{};

	// Ignore the last "w" row
	for (unsigned int row = 0; row < 4 - 1; row++)
	{
		for (unsigned int col = 0; col < 1; col++)
		{
			result += one.GetVal(row, col) * two.GetVal(row, col);
		}
	}

	return result;
}

double MatrixHelper::Length(const Vector3D& one) const
{
	double result{};

	for (unsigned int col = 0; col < 1; col++)
	{
		// Ignore the last "w" row
		for (unsigned int row = 0; row < 4 - 1; row++)
		{
			result += one.GetVal(row, col) * one.GetVal(row, col);
		}
	}

	result = sqrt(result);
	return result;
}

MatrixHelper::Vector3D MatrixHelper::Normalize(const Vector3D& one) const
{
	// TODO(Sander Mol): Errror when cols <= 1 ?
	Vector3D result{};

	// Ignore the last "w" row
	for (unsigned int col = 0; col < 1; col++)
	{
		auto r = one.GetCol(col);

		// quick-fix for convert
		Vector3D vector(
			{
				{r[0]},
				{r[1]},
				{r[2]},
				{r[3]} // or 1?
			}
		);
		const auto length = Length(vector);

		for (unsigned int row = 0; row < 4 - 1; row++)
		{
			const auto normalized = vector.GetVal(row, col) / length;

			result.SetVal(row, col, normalized);
		}
	}

	return result;
}

MatrixHelper::Vector3D MatrixHelper::Cross(const Vector3D& one, const Vector3D& two) const
{
	// TODO(Sander Mol): Errror when cols > 1 ?

	// TODO(Sander Mol): functionality equals to `this * ofMatrix` ?
	return Vector3D(
		{
			{one.GetVal(1, 0) * two.GetVal(2, 0) - one.GetVal(2, 0) * two.GetVal(1, 0)}, // ay * bz - az * by
			{one.GetVal(2, 0) * two.GetVal(0, 0) - one.GetVal(0, 0) * two.GetVal(2, 0)}, // az * bx - ax * bz
			{one.GetVal(0, 0) * two.GetVal(1, 0) - one.GetVal(1, 0) * two.GetVal(0, 0)}, // ax * by - ay * bx
			{1} // default value 1 for "w", so it indicates a non-scalar matrix
		}
	);
}
