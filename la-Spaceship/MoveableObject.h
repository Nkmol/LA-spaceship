#pragma once 
#include "Object.h" 
class MoveableObject : 
  public Object 
{ 
private: 
	using Object::Object; 
 
	double _velocity = 1.1; 
	Vector3d<unsigned> _direction = {
		0,
		0,
		1
	};
public: 
	void Update();
	void SetDirection(const Vector3d<unsigned>& direction);
	void SetVelocity(double value);
	double GetVelocity() const;
}; 