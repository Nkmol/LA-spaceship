#include "Bullet.h"
#include "Models.h"

Bullet::Bullet(double x, double y, double z, const Vector3d<double>& direction, double velocity)
	: Object({x, y, z}, {1, 1, 1}, Models::Cube::matrix)
{
	MoveableObject::SetVelocity(velocity + bullet_velocity);
	MoveableObject::SetDirection(direction);
}

void Bullet::Update()
{
	const Matrix<double, 4, 1> origin_m = {
		{_local_origin_point.GetX()},
		{_local_origin_point.GetY()},
		{_local_origin_point.GetZ()},
		{1}
	};
	const auto result = GetMovementTransform() * origin_m;

	_local_origin_point = {result.GetVal(0, 0), result.GetVal(1, 0), result.GetVal(2, 0)};
}
