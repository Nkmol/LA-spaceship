#pragma once
#include "Object.h"
#include "MoveableObject.h"

class Bullet :
	public Object, MoveableObject
	
{
private:
	Matrix<double, 4, 1> local_point;
	const double bullet_velocity = 50;

public:
	Bullet(double x, double y, double z, Vector3d<double> direction, double acceleration);
	
	void Update();
	void Draw(Camera& camera);
};

