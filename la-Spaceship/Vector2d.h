#pragma once
#include <iostream>
class Vector2d
{
public:
	Vector2d(double _x, double _y);
	Vector2d operator*(double factor);
	Vector2d operator+(Vector2d& other);
	Vector2d operator-(Vector2d& other);
	double GetX() const;
	double GetY() const;
	friend std::ostream& operator<<(std::ostream& cout, Vector2d& vector);
private:
	double x;
	double y;
};

