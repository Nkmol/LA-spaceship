#include "MatrixHelper.h"

Matrix<double, 4, 4> MatrixHelper::Rotate(double angle_percentage, Matrix<double, 4, 4> matrix, double x, double y,
	double z)
{
	MatrixFactory factory;

	const double rad = factory. AngleToRadian(angle_percentage);

	const double t1 = atan2(z, x);
	const double t2 = atan2(y, sqrt(pow(x, 2) + pow(z, 2)));

	const auto z_rot = factory.CreateRotationMatrix(t1, Z, true);
	const auto y_rot = factory.CreateRotationMatrix(t2, Y, true);
	const auto x_rot = factory.CreateRotationMatrix(rad, X, true);
	const auto y_ret = factory.CreateRotationMatrix(-t2, Y, false);
	const auto z_ret = factory.CreateRotationMatrix(-t1, Z, false);

	return (z_ret * (y_ret * (x_rot * (y_rot * z_rot)))) * matrix;
}
