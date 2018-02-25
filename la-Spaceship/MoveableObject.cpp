#include "MoveableObject.h"
#include "MatrixHelper.h"

Matrix<double, 4, 4> MoveableObject::GetMovementTransform()
{
	MatrixFactory factory;
	MatrixHelper helper;

	return
		factory.CreateTranslationMatrix(
			_direction.GetX() * _velocity,
			_direction.GetY() * _velocity,
			_direction.GetZ() * _velocity);
}

void MoveableObject::SetDirection(const Vector3d<double>& direction)
{
	_direction = direction;
}

void MoveableObject::SetVelocity(const double value)
{
	if (value < 0)
	{
		_velocity = 0;
	}
	else
	{
		_velocity = value;
	}
}

double MoveableObject::GetVelocity() const
{
	return _velocity;
}
