#include "MatrixHelper.h"

Matrix<double, 4, 4> MatrixHelper::Rotate(double angle_percentage, Matrix<double, 4, 4> matrix, double x, double y,
	double z)
{
	MatrixFactory factory;

	const double rad = factory.AngleToRadian(angle_percentage);

	const double t1 = atan2(z, x); // Rad to rotate z edge to 0
	const double t2 = atan2(y, sqrt(pow(x, 2) + pow(z, 2))); // Rad to rotate y edge to 0

	const auto z_rot = factory.CreateRotationMatrix(t1, Z, true); // Rotate Z edge to 0
	const auto y_rot = factory.CreateRotationMatrix(t2, Y, true); // Rotate Y edge to 0
	const auto x_rot = factory.CreateRotationMatrix(rad, X, true); // Rotate around the given edge
	const auto y_ret = factory.CreateRotationMatrix(-t2, Y, false); // Rotate Y edge back
	const auto z_ret = factory.CreateRotationMatrix(-t1, Z, false); // Rotate Z edge back

	return (z_ret * (y_ret * (x_rot * (y_rot * z_rot)))) * matrix;
}
