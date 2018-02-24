#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <initializer_list>
#include <iomanip>

#define MTXTMP template <typename T, unsigned int rows, unsigned int cols>

/* Matrix class template */
MTXTMP
class Matrix
{
protected:
	std::array<std::array<T, cols>, rows> _myVal;
public:
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<T>> list);
	virtual ~Matrix();

	std::array<T, cols> GetRow(unsigned int row) const;
	std::array<T, rows> GetCol(unsigned int col) const;
	T GetVal(unsigned int row, unsigned int col) const;
	void SetVal(unsigned int row, unsigned int col, T val);

	Matrix<T, cols, rows> Transpose() const;
	Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols>& operand) const;
	Matrix<T, rows, cols>& operator+=(const Matrix<T, rows, cols>& operand);
	Matrix<T, rows, cols> operator-() const;
	Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols>& operand) const;
	Matrix<T, rows, cols>& operator-=(const Matrix<T, rows, cols>& operand);
	Matrix<T, rows, cols> operator*(T operand) const;
	Matrix<T, rows, cols>& operator*=(T operand);
	template <unsigned int opcols>
	Matrix<T, rows, opcols> operator*(const Matrix<T, cols, opcols>& operand) const;
};

MTXTMP
Matrix<T, rows, cols>::~Matrix() = default;

/* Default constructor */
MTXTMP
Matrix<T, rows, cols>::Matrix() : _myVal({})
{
	static_assert(rows * cols > 0, "Invalid size of matrix");
}

/* Constructor with initializer list */
MTXTMP
Matrix<T, rows, cols>::Matrix(std::initializer_list<std::initializer_list<T>> list)
{
	static_assert(rows * cols > 0, "Invalid size of matrix");
	unsigned int row = 0;
	for (auto k = list.begin(); k != list.end(); ++k)
	{
		unsigned int col = 0;
		for (auto l = k->begin(); l != k->end(); ++l)
		{
			_myVal[row][col++] = *l;
		}
		++row;
	}
}

/* Row getter */
MTXTMP
std::array<T, cols> Matrix<T, rows, cols>::GetRow(const unsigned int row) const
{
	return std::array<T, cols>(_myVal[row]);
}

/* Column getter */
MTXTMP
std::array<T, rows> Matrix<T, rows, cols>::GetCol(const unsigned int col) const
{
	std::array<T, rows> result;
	for (unsigned int i = 0; i < rows; i++) {
		result[i] = _myVal[i][col];
	}
	return result;
}

/* Getter */
MTXTMP
T Matrix<T, rows, cols>::GetVal(const unsigned int row, const unsigned int col) const
{
	return _myVal[row][col];
}

/* Setter */
MTXTMP
void Matrix<T, rows, cols>::SetVal(unsigned int row, unsigned int col, const T val)
{
	_myVal[row][col] = val;
}

/* Transpose */
MTXTMP
Matrix<T, cols, rows> Matrix<T, rows, cols>::Transpose() const
{
	Matrix<T, cols, rows> result {};
	for (unsigned int i = 0; i < cols; i++) {
		for (unsigned int j = 0; j < rows; j++) {
			result.SetVal(i, j, _myVal[j][i]);
		}
	}
	return result;
}

/* Negation */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator-() const
{
	return (*this) * static_cast<T>(-1);
}

/* Addition */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator+(const Matrix<T, rows, cols>& operand) const
{
	Matrix<T, rows, cols> result {};
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			result._myVal[i][j] = _myVal[i][j] + operand._myVal[i][j];
		}
	}
	return result;
}

MTXTMP
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator+=(const Matrix<T, rows, cols>& operand)
{
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			_myVal[i][j] += operand._myVal[i][j];
		}
	}
	return *this;
}

/* Subtraction */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator-(const Matrix<T, rows, cols>& operand) const
{
	return (*this) + (-operand);
}

MTXTMP
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator-=(const Matrix<T, rows, cols>& operand)
{
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			_myVal[i][j] -= operand._myVal[i][j];
		}
	}
	return *this;
}

/* Scalar multiplication */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator*(const T operand) const
{
	Matrix<T, rows, cols> result {};
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			result._myVal[i][j] = _myVal[i][j] * operand;
		}
	}

	return result;
}

MTXTMP
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(const T operand)
{
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			_myVal[i][j] *= operand;
	return *this;
}

/* Matrix multiplication */
// cols need to differ
MTXTMP
template <unsigned int opcols>
Matrix<T, rows, opcols> Matrix<T, rows, cols>::operator*(const Matrix<T, cols, opcols>& operand) const
{
	Matrix<T, rows, opcols> ans = {};
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < opcols; j++)
		{
			for (unsigned int k = 0; k < cols; k++) {
				ans.SetVal(i, j, ans.GetVal(i, j) + this->GetVal(i, k) * operand.GetVal(k, j));
			}
		}
	}
	return ans;
}

MTXTMP
std::ostream& operator<<(std::ostream& cout, const Matrix<T, rows, cols>& matrix)
{
	for (unsigned int row = 0; row < rows; ++row)
	{
		for(unsigned int col = 0; col < cols; ++col)
		{
			cout << std::setw(10) << matrix.GetVal(row, col) << " ";
		}
		cout << std::endl;
	}

	return cout;
}

#endif
