#pragma once 
#include "Object.h" 
class MoveableObject
{ 
private: 
	double _velocity = 1.1; 
	Vector3d<double> _direction = {
		0,
		0,
		0
	};
public: 
	Matrix<double, 4, 4> GetMovementTransform();
	void SetDirection(const Vector3d<double>& direction);
	void SetVelocity(double value);
	double GetVelocity() const;
}; 