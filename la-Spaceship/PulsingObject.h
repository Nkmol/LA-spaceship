#pragma once
#include "Object.h"
#include "Camera.h"

class PulsingObject :
	public Object
{
	using Object::Object;

private:
	bool _grow = true;

	// Amount of pulsation per frame/update
	const double _pulseAmount = 0.05;
	double _totalAmountPulsed = 0;
public:

	void Update();
};

