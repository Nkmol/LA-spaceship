#include "Matrix.h"
#include <assert.h>
#include <sstream>



Matrix::Matrix()
{
}

Matrix::Matrix(int height, int width)
{
	this->height = height;
	this->width = width;
	this->collection = std::vector<std::vector<double> >(height, std::vector<double>(width));
}

Matrix::Matrix(std::vector<std::vector<double>> const & arr)
{
	assert(arr.size() != 0);
	this->height = arr.size();
	this->width = arr[0].size();
	this->collection = arr;
}

Matrix Matrix::multiply(double const & val)
{
	Matrix result{ height, width };
	int i, n;

	for (i = 0; i < height; i++)
	{
		for (n = 0; i < width; n++)
		{
			result.collection[i][n] = collection[i][n] * val;
		}
	}

	return result;
}

Matrix Matrix::add(Matrix const & m) const
{
	assert(height == m.height && width == m.width);

	Matrix result{ height, width };
	int i, n;

	for (i = 0; i < height; i++)
	{
		for (n = 0; i < width; n++)
		{
			result.collection[i][n] = collection[i][n] + m.collection[i][n];
		}
	}

	return result;
}

Matrix Matrix::subtract(Matrix const & m) const
{
	assert(height == m.height && width == m.width);

	Matrix result{ height, width };
	int i, n;

	for (i = 0; i < height; i++)
	{
		for (n = 0; i < width; n++)
		{
			result.collection[i][n] = collection[i][n] - m.collection[i][n];
		}
	}

	return result;
}

Matrix Matrix::multiply(Matrix const & m) const
{
	assert(height == m.height && width == m.width);

	Matrix result{ height, width };
	int i, n;

	for (i = 0; i < height; i++)
	{
		for (n = 0; n < width; n++)
		{
			result.collection[i][n] = collection[i][n] * m.collection[i][n];
		}
	}

	return result;
}

Matrix Matrix::dot(Matrix const & m) const
{
	assert(height == m.width);

	int i, n, h, m_width = m.width;
	double w = 0;

	Matrix result{ height, m_width };

	for (i = 0; i < height; i++)
	{
		for (n = 0; n < m_width; n++)
		{
			for (h = 0; h < width; h++)
			{
				w += collection[i][h] * m.collection[h][n];
			}
			result.collection[i][n] = w;
			w = 0;
		}
	}

	return result;
}

Matrix Matrix::transpose() const
{
	Matrix result{ width, height };
	int i, n;

	for (i = 0; i < width; i++)
	{
		for (n = 0; n < height; n++)
		{
			result.collection[i][n] = collection[n][i];
		}
	}

	return result;
}

Matrix Matrix::applyFunction(double(*function)(double)) const
{
	Matrix result{ width, height };
	int i, n;

	for (i = 0; i < height; i++)
	{
		for (n = 0; n < width; n++)
		{
			result.collection[i][n] = (*function)(collection[i][n]);
		}
	}

	return result;
}

void Matrix::print(std::ostream & out) const
{
	int i, n;
	std::vector<int> max_length(width);
	std::stringstream ss;

	for (i = 0; i < height; i++)
	{
		for (n = 0; n < width; n++)
		{
			ss << collection[i][n];
			if (max_length[n] < ss.str().size())
			{
				max_length[n] = ss.str().size();
			}

			ss.str(std::string());
		}
	}

	for (i = 0; i < height; i++)
	{
		for (n = 0; n < width; n++)
		{
			out << collection[i][n];
			ss << collection[i][n];

			for (int j = 0; j < max_length[n] - ss.str().size() + 1; j++)
			{
				out << " ";
			}

			ss.str(std::string());
		}

		out << std::endl;
	}
}

std::ostream & operator<<(std::ostream & out, const Matrix & m)
{
	m.print(out);
	return out;
}
