#include "PulsingObject.h"

void PulsingObject::Update()
{
	MatrixFactory factory;

	Matrix<double, 4, 4> scalar;
	if(_grow)
	{
		scalar = factory.CreateScaleMatrix(1 + _pulseAmount, 1 + _pulseAmount, 1 + _pulseAmount);
	}
	else
	{
		scalar  = factory.CreateScaleMatrix(1 - _pulseAmount, 1 - _pulseAmount, 1 - _pulseAmount);
	}

	_amountPulse +=_pulseAmount;
	if(_amountPulse >= 2)
	{
		_grow = !_grow;
		_amountPulse = 0;
	}

	Scale(scalar);
}
