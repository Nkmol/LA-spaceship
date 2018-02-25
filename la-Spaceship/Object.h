#pragma once
#include "Matrix.h"
#include <vector>
#include "Vector3d.h"
#include "RenderManager.h"
#include "MatrixFactory.h"
#include <iostream>
#include "Camera.h"

class Object
{
private:
	std::vector<Vector3d<double> >  _points;
	std::vector<std::pair<unsigned int, unsigned int>> _lines;

	Vector3d<double> _local_origin_point = {0, 0, 0};
	// TODO matrix named _transform, currently unable due to matrix requiring a template.
public:
	Object() = default;

	template<unsigned width>
	Object(const Vector3d<double>& location, const Vector3d<double>& size, const Matrix<double, 4, width>& model)
	{
		MatrixFactory factory;

		_local_origin_point = location;
		const auto si = factory.CreateScaleMatrix(size.GetX(), size.GetY(), size.GetZ());

		SetTransform(si*model);
	}

	const std::vector<std::pair<unsigned int, unsigned int>>& GetLines() const
	{
		return _lines;
	}

	void SetLines(const std::vector<std::pair<unsigned int, unsigned int>>& lines)
	{
		_lines = lines;
	}

	const std::vector<Vector3d<double>>& GetPoints() const
	{
		return _points;
	}

	Matrix<double, 4, 1> GetCenterPoint()
    {
        double x = 0, y = 0, z = 0;
        const auto size = _points.size();

        for(unsigned int row = 0; row < size; row++)
        {
            auto& val = _points[row];
            x += val.GetX();
            y += val.GetY();
            z += val.GetZ();
        }

        x /= size;
        y /= size;
        z /= size;

        return Matrix<double, 4, 1>( 
            {
                {x},
                {y},
                {z},
                {1}
            }
        );
    }

	void SetTransform(const std::vector<Vector3d<double>>& points)
	{
		_points = points;
	}
	
	template<unsigned int width>
	void SetTransform(const Matrix<double, 4, width>& matrix)
	{
		_points = ToPoints(matrix);
	}

	template<unsigned int width>
	static std::vector<Vector3d<double>> ToPoints(const Matrix<double, 4, width>& matrix) 
	{
		std::vector<Vector3d<double>> result {};
		for (unsigned int x = 0; x < width; x++)
		{
			result.push_back({ matrix.GetVal(0, x), matrix.GetVal(1, x), matrix.GetVal(2, x)});
		}

		return result;
	}

	template<int width>
	static Matrix<double, 4, width> ToMatrix(const std::vector<Vector3d<double>>& points)
	{
		Matrix<double, 4, width> matrix;

		for(unsigned int x = 0; x < width && x < points.size(); x++)
		{
			auto& point = points[x];
			matrix.SetVal(0, x, point.GetX());
			matrix.SetVal(1, x, point.GetY());
			matrix.SetVal(2, x, point.GetZ());
			matrix.SetVal(3, x, 1);
		}

		return matrix;
	}

	int count = 0;

	void Scale(const Matrix<double, 4, 4>& scalar)
	{
		MatrixFactory factory;
		const auto center = GetCenterPoint();

		// TODO hardcoded size
		auto matrix = ToMatrix<8>(GetPoints());

		// Translate center to origin
		const auto translateToOrigin = factory.CreateTranslationMatrix(
			-center.GetVal(0, 0), // X
			-center.GetVal(1, 0), // Y
			-center.GetVal(2, 0)  // Z
		);
		// Reverse translate center to origin
		const auto minTranslateToOrigin = factory.CreateTranslationMatrix(
			center.GetVal(0, 0), // X
			center.GetVal(1, 0), // Y
			center.GetVal(2, 0)  // Z
		);

		// Left to right
		const auto transformation =  minTranslateToOrigin * scalar * translateToOrigin;
		//std::cout << std::to_string(count) << " - " << (oldMatrix).GetVal(0, 0) << " - " << (matrix - oldMatrix).GetVal(0, 0) << std::endl;
		matrix = transformation * matrix;

		SetTransform(matrix);
	}
};

