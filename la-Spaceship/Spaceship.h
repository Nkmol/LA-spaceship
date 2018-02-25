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

public:
	Spaceship();

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


