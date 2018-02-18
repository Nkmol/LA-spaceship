#include "Matrix3d.h"


Matrix3d::Matrix3d(Vector3dCollection collection, bool without_loss)
	: Matrix(CreateFromVector(collection, without_loss))
{

}

Matrix3d::Matrix3d(const Matrix m)
	: Matrix(CreateFromMatrix(m))
{

}

Matrix3d Matrix3d::dot(Matrix3d const& m) const
{
	return Matrix::dot(m);
}


Matrix3d::NestedVector Matrix3d::CreateFromVector(Vector3dCollection data, bool without_loss)
{
	std::vector<std::vector<double>> content;

	if (without_loss)
	{
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			auto& vec = *it;

			content.push_back({ vec.GetX(), vec.GetY(), vec.GetZ(), static_cast<double>((it == (data.end()))) });
		}

		content.push_back({ 0, 0, 0, 1 });
	}
	else
	{
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			auto& vec = *it;

			content.push_back({ vec.GetX(), vec.GetY(), vec.GetZ(), 1 });
		}
	}

	return content;
}

Matrix3d::NestedVector Matrix3d::CreateFromMatrix(const Matrix m)
{
	assert(m.height == 4);

	return m.collection;
}

std::ostream& operator<<(std::ostream& out, const Matrix3d& m)
{
	m.print(out);

	return out;
}
