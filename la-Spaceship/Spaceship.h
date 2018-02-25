#pragma once
#include "Object.h"
#include "Camera.h"
#include "MatrixHelper.h"

class Spaceship
{
private:
	Object engine;
	Object body;
	Object head;
	Object left_wing;
	Object right_wing;
	Matrix<double, 4, 1> local_origin_point;

public:
	Spaceship(double x, double y, double z);

	void Draw(Camera& camera);
	void Rotate(double rotate_percentage, Axis axis);

	// Init parts
	void Init();
	void ConstructEngine();
	void ConstructBody();
	void ConstructHead();
	void ConstructLeftWing();
	void ConstructRightWing();
};


