#pragma once
#include <vector>
#include <iostream>

class Matrix
{
protected:
	Matrix();
	Matrix(int height, int width);
	Matrix(std::vector<std::vector<double> > const &arr);
	
	Matrix multiply(double const &val); // scalar multiplication.

	Matrix add(Matrix const &m) const;
	Matrix subtract(Matrix const &m) const;
	Matrix multiply(Matrix const &m) const; // hadamard product.

	Matrix dot(Matrix const &m) const; // dot product.
	Matrix transpose() const; // transposed matrix.
	Matrix applyFunction(double(*function)(double)) const; // apply function to every element of the matrix.


public:
	friend std::ostream& operator<<(std::ostream &out, const Matrix &m); // Overloading to print easily.
	void print(std::ostream &out) const; // Print the matrix.

	std::vector<std::vector<double> > collection;
	int height;
	int width;
};
