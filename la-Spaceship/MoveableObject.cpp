#include "MoveableObject.h"
#include "MatrixHelper.h"

void MoveableObject::Update()
{
	MatrixFactory factory;
	MatrixHelper helper;
	// TODO hardcoded size
	const auto matrix = ToMatrix<8>(GetPoints());

	SetTransform(
		factory.CreateTranslationMatrix(
			_direction.GetX() * _velocity, 
			_direction.GetY() * _velocity, 
			_direction.GetZ() * _velocity)
		* matrix);
}

void MoveableObject::SetDirection(const Vector3d<unsigned>& direction)
{
	_direction = direction;
}

void MoveableObject::SetVelocity(const double value)
{
	_velocity = value;
}

double MoveableObject::GetVelocity() const
{
	return _velocity;
}
