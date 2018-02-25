#include "PulsingObject.h"
#include <iostream>


PulsingObject::PulsingObject(double x, double y, double z)
	: local_origin_point({ {x}, {y}, {z}, {1} })
{
}

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

void PulsingObject::Draw(Camera& camera)
{
	MatrixFactory factory;


	// Transform
	const auto translate = factory.CreateTranslationMatrix(
		local_origin_point.GetVal(0, 0), 
		local_origin_point.GetVal(1, 0),
		local_origin_point.GetVal(2, 0)
	);

	const auto transform = translate * Object::ToMatrix<8>(GetPoints());

	// Projection
	const auto projection = camera.ProjectMatrix(transform);

	// Draw
	RenderManager::GetInstance().DrawPoints(Object::ToPoints(projection), GetLines());
}
