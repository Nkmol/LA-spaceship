#pragma once
#include "Object.h"
class PulsingObject :
	public Object
{
private:
	bool _grow = true;
	double _pulseAmount = 0.1;
	double _amountPulse = 0;
public:
	using Object::Object;

	void Update();
};

