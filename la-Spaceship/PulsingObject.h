#pragma once
#include "Object.h"
#include "Camera.h"

class PulsingObject :
	public Object
{
private:
	bool _grow = true;
	Matrix<double, 4, 1> local_origin_point;

	// Amount of pulsation per frame/update
	const double _pulseAmount = 0.05;
	double _totalAmountPulsed = 0;
public:
	using Object::Object;
	PulsingObject(double x, double y, double z);

	void Update();
	void Draw(Camera& camera);
};

