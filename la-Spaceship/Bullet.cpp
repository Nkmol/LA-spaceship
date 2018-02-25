#include "Bullet.h"

Bullet::Bullet(double x, double y, double z, Vector3d<double> direction, double velocity)
	: local_point({ { x },{ y },{ z },{ 1 } })
{
	MoveableObject::SetVelocity(velocity + bullet_velocity);
	MoveableObject::SetDirection(direction);
}

void Bullet::Update()
{
	local_point = GetMovementTransform() * local_point;
}

void Bullet::Draw(Camera& camera)
{
	MatrixFactory factory;

	// Transform
	const auto translate = factory.CreateTranslationMatrix(
		local_point.GetVal(0, 0),
		local_point.GetVal(1, 0),
		local_point.GetVal(2, 0)
	);

	const auto engine_transform = translate * Object::ToMatrix<8>(GetPoints());

	// Create Projection
	const auto projection = camera.ProjectMatrix(engine_transform);

	// Draw objects
	RenderManager::GetInstance().DrawPoints(Object::ToPoints(projection), GetLines());
}
