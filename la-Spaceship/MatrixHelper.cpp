#include "MatrixHelper.h"

Matrix<double, 4, 4> MatrixHelper::Rotate(double angle_percentage, Matrix<double, 4, 4> matrix,
	std::vector<double> edge_begin, std::vector<double> edge_end)
{
	MatrixFactory factory;
	
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

	return (revert * (z_ret * (y_ret * (x_rot * (y_rot * (z_rot * translate)))))) * matrix;
}
