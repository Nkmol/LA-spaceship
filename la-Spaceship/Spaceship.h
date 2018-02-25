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
	Object help_lines;
	Matrix<double, 4, 1> local_origin_point;

	bool show_help_lines = true;

	std::vector<Bullet> bullets;

public:
	Spaceship(double x, double y, double z);

	void Shoot();
	void Draw(Camera& camera);
	void Rotate(double rotate_percentage, Axis axis);
	void Accelerate(double amount);
	void Update();
	void ToggleHelpLines();

	// Init parts
	void Init();
	void ConstructEngine();
	void ConstructBody();
	void ConstructHead();
	void ConstructLeftWing();
	void ConstructRightWing();
	void ConstructHelpLines();
};


