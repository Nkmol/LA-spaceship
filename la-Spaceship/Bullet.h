#pragma once
#include "Object.h"
#include "MoveableObject.h"

class Bullet :
	public Object, MoveableObject
	
{
	using Object::Object;
private:
	const double bullet_velocity = 50;

public:
	Bullet(double x, double y, double z, const Vector3d<double>& direction, double velocity);

	void Update();
};

