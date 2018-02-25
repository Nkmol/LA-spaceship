#pragma once
#include "Object.h"
class PulsingObject :
	public Object
{
private:
	bool _grow = true;
	// Amount of pulsation per frame/update
	const double _pulseAmount = 0.05;
	double _totalAmountPulsed = 0;
public:
	using Object::Object;

	void Update();
};

