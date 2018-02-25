#pragma once
#include "Object.h"
#include "Camera.h"

class PulsingObject :
	public Object
{
private:
	bool _grow = true;
	double _pulseAmount = 0.1;
	double _amountPulse = 0;
	Matrix<double, 4, 1> local_origin_point;

public:
	using Object::Object;
	PulsingObject(double x, double y, double z);

	void Update();
	void Draw(Camera& camera);
};

