#pragma once
#include "Matrix.h"
#include "Vector3d.h"
#include <cassert>

class Matrix3d :
	protected Matrix
{
public:
	typedef std::vector<std::vector<double>> NestedVector;
	typedef std::vector<Vector3d> Vector3dCollection;

	Matrix3d(Vector3dCollection collection, bool without_loss);
	Matrix3d(Matrix m);
	Matrix3d dot(Matrix3d const &m) const;

	friend std::ostream& operator<<(std::ostream &out, const Matrix3d &m);
	
private:
	NestedVector CreateFromVector(Vector3dCollection data, bool without_loss);
	NestedVector CreateFromMatrix(const Matrix m);

};

