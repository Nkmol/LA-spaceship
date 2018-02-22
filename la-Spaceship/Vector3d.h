#pragma once

template<typename T>
class Vector3d
{
public:
	Vector3d(T x, T y, T z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	T GetX()
	{
		return _x;
	}

	T GetY()
	{
		return _y;
	}

	T GetZ()
	{
		return _z;
	}

private:
	T _x;
	T _y;
	T _z;
};