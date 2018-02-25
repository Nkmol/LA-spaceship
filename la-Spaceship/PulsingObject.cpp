#include "PulsingObject.h"

PulsingObject::PulsingObject(double x, double y, double z)
	: local_origin_point({ {x}, {y}, {z}, {1} })
{
}

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
