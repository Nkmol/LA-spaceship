//#include "MatrixFactory.h"
//
//Matrix3d MatrixFactory::CreateTranslationMatrix(const Vector2d& addition) const
//{
//	std::vector<Vector3d> vec;
//
//	vec.push_back(Vector3d{ 1, 0, 0 });
//	vec.push_back(Vector3d{ 0, 1, 0 });
//	vec.push_back(Vector3d{ addition.GetX(), addition.GetY(), 1 });
//
//	return vec;
//}
//Matrix2d MatrixFactory::CreateScalingMatrix(const Vector2d & scaling) const
//{
//	std::vector<Vector2d> vec;
//
//	vec.push_back(Vector2d{ scaling.GetX(), 0});
//	vec.push_back(Vector2d{ 0, scaling.GetY() });
//
//	return vec;
//}
//
//Matrix2d MatrixFactory::Create2dRotationMatrix(double angle_percentage) const
//{
//	std::vector<Vector2d> vec;
//
//	double rad = AngleToRadian(angle_percentage);
//
//	vec.push_back(Vector2d{ cos(rad), sin(rad) });
//	vec.push_back(Vector2d{ -sin(rad), cos(rad) }); // TODO double cos
//	return vec;
//}
//
//Matrix2d MatrixFactory::Create2dNulMatrix() const
//{
//	std::vector<Vector2d> vec;
//
//	vec.push_back(Vector2d{ 0, 0 });
//	vec.push_back(Vector2d{ 0, 0 });
//
//	return vec;
//}
//
//Matrix2d MatrixFactory::Create2dIdentityMatrix() const
//{
//	std::vector<Vector2d> vec;
//
//	vec.push_back(Vector2d{ 1, 0 });
//	vec.push_back(Vector2d{ 0, 1 });
//
//	return vec;
//}
//
//double MatrixFactory::AngleToRadian(double angle_percentage) const // TODO more accurate solution
//{
//	return (angle_percentage / 180.0) * ((double)M_PI);
//}
//
//Matrix MatrixFactory::CreateTranslationMatrix(const Vector3d & addition) const
//{
//	std::vector<std::vector<double>> collection;
//
//	collection.push_back(std::vector<double>{1, 0, 0, addition.GetX() });
//	collection.push_back(std::vector<double>{0, 1, 0, addition.GetY() });
//	collection.push_back(std::vector<double>{0, 0, 1, addition.GetZ() });
//	collection.push_back(std::vector<double>{0, 0, 0, 1 });
//
//	return collection;
//}
//
//Matrix3d MatrixFactory::CreateScalingMatrix(const Vector3d & scaling) const
//{
//	std::vector<Vector3d> collection;
//
//	collection.push_back(Vector3d{scaling.GetX(), 0, 0 });
//	collection.push_back(Vector3d{0, scaling.GetY(), 0 });
//	collection.push_back(Vector3d{0, 0, scaling.GetZ() });
//
//	return collection;
//}
//
//Matrix3d MatrixFactory::CreateRotationMatrix(double angle_percentage, const Vector3d& edge_begin, const Vector3d& edge_end) const
//{
//	std::vector<Vector3d> collection;
//	
//	const double rad = AngleToRadian(angle_percentage);
//
//	const double t1 = atan2(edge_end.GetZ(), edge_end.GetX());
//
//	Matrix3d z = CreateRotationMatrix(t1, Z);
//	Vector3d r = z.vector_dot(edge_end);
//
//	const double t2 = atan2(edge_end.GetY(), sqrt(r.GetX() + r.GetZ()));
//
//
//	return collection;
//}
//
//Matrix3d MatrixFactory::CreateRotationMatrix(double angle_percentage, const Axis axis) const
//{
//	std::vector<Vector3d> collection;
//
//	const double rad = AngleToRadian(angle_percentage);
//
//	if (axis == X)
//	{
//		collection.push_back(Vector3d{ 1, 0, 0 });
//		collection.push_back(Vector3d{ 0, cos(rad), -sin(rad) });
//		collection.push_back(Vector3d{ 0, sin(rad), cos(rad) });
//	}
//	else if (axis == Y)
//	{
//		collection.push_back(Vector3d{ cos(rad), 0, -sin(rad) });
//		collection.push_back(Vector3d{ 0, 1, 0 });
//		collection.push_back(Vector3d{ sin(rad), 0, cos(rad) });
//	}
//	else if (axis == Z)
//	{
//		collection.push_back(Vector3d{ cos(rad), -sin(rad), 0 });
//		collection.push_back(Vector3d{ sin(rad), cos(rad), 0 });
//		collection.push_back(Vector3d{ 0, 0, 1 });
//	}
//
//	return collection;
//}
//
//Matrix3d MatrixFactory::CreateNulMatrix() const
//{
//	std::vector<Vector3d> collection;
//
//	collection.push_back(Vector3d{ 0, 0, 0 });
//	collection.push_back(Vector3d{ 0, 0, 0 });
//	collection.push_back(Vector3d{ 0, 0, 0 });
//
//	return collection;
//}
//
//Matrix3d MatrixFactory::CreateIdentityMatrix() const
//{
//	std::vector<Vector3d> collection;
//
//	collection.push_back(Vector3d{ 1, 0, 0 });
//	collection.push_back(Vector3d{ 0, 1, 0 });
//	collection.push_back(Vector3d{ 0, 0, 1 });
//
//	return collection;
//}
