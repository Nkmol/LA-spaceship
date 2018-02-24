#pragma once
#include "Matrix.h"
#include <vector>
#include "Vector3d.h"
#include "RenderManager.h"

class Object
{
public:
	void SetTransform(std::vector<Vector3d<double> > points)
	{
		_points = points;
	}

	template<int width>
	void FromMatrix(const Matrix<double, 4, width>& matrix)
	{
		_points.clear();

		for (int x = 0; x < width; x++)
		{
			_points.push_back({ matrix.GetVal(0, x), matrix.GetVal(1, x), matrix.GetVal(2, x)});
		}
	}

	// TODO Temporary fix for using matrixes with constant sizes.
	template<int w>
	Matrix<double, 4, w> ToMatrix()
	{
		Matrix<double, 4, w> matrix;

		for(int x = 0; x < w && x < _points.size(); x++)
		{
			auto& point = _points[x];
			matrix.SetVal(0, x, point.GetX());
			matrix.SetVal(1, x, point.GetY());
			matrix.SetVal(2, x, point.GetZ());
			matrix.SetVal(3, x, 1);
		}

		return matrix;
	}

	void Draw()
	{
		// TODO 3d to 2d before drawing (finish transform)

		RenderManager& render_manager = RenderManager::GetInstance();

		for (auto begin = _points.begin(); begin < _points.end(); ++begin)
		{
			auto end = begin;
			
			if (begin == _points.end() - 1)
			{
				end = _points.begin();
			}
			else
			{
				end++;
			}

			render_manager.Draw(
				{ (*begin).GetX(), (*begin).GetY() }, 
				{ (*end).GetX(), (*end).GetY() }
			);
		}

	}

private:
	std::vector<Vector3d<double> >  _points;
	// TODO matrix named _transform, currently unable due to matrix requiring a template.
};

