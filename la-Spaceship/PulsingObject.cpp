#include "PulsingObject.h"
#include <iostream>


void PulsingObject::Update()
{
	count++;

	MatrixFactory factory;

	Matrix<double, 4, 4> scaleMatrix;
	if(_grow)
	{
		const auto scalar = 1 + _pulseAmount;
		scaleMatrix = factory.CreateScaleMatrix(scalar, scalar, scalar);
	}
	else
	{
		// decrease with same %, so from 110% with a step of +10% back to 100%
		const auto scalar = 100 / ((1 + _pulseAmount) * 100);
		scaleMatrix  = factory.CreateScaleMatrix(scalar, scalar, scalar);
	}

	_totalAmountPulsed += _pulseAmount;
	if(_totalAmountPulsed >= 1.5)
	{
		_grow = !_grow;
		_totalAmountPulsed = 0;
	}

	Scale(scaleMatrix);
}
