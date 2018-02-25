#pragma once
#include "Object.h"
#include "Camera.h"
#include "MatrixHelper.h"
#include "MoveableObject.h"
#include "Bullet.h"

class Spaceship
	: MoveableObject
{
private:
	Object engine;
	Object body;
	Object head;
	Object left_wing;
	Object right_wing;
	Matrix<double, 4, 1> local_origin_point;

	std::vector<Bullet> bullets;

public:
	Spaceship(double x, double y, double z);

	void Shoot();
	void Draw(Camera& camera);
	void Rotate(double rotate_percentage, Axis axis);
	void Accelerate(double amount);
	void Update();

	// Init parts
	void Init();
	void ConstructEngine();
	void ConstructBody();
	void ConstructHead();
	void ConstructLeftWing();
	void ConstructRightWing();
};


