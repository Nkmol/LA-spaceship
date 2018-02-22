#pragma once

template<typename T>
class Vector2d
{
public:
	Vector2d(T x, T y)
	{
		_x = x;
		_y = y;
	}

	T GetX() const
	{
		return _x;
	}

	T GetY() const
	{
		return _y;
	}

private:
	T _x;
	T _y;
};