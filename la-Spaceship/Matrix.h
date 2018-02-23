///mostly based on https://gist.github.com/MihailJP/3937550

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
	std::array<std::array<T, cols>, rows> myVal;

private:

	template <typename T_, unsigned int rows_, unsigned int cols_>
	struct calc_det
	{
		T_ operator()(const Matrix<T_, rows_, cols_>&) const;
	};

	template <typename T_>
	struct calc_det<T_, 1, 1>
	{
		T_ operator()(const Matrix<T_, 1, 1>&) const;
	};

	template <typename T_>
	struct calc_det<T_, 2, 2>
	{
		T_ operator()(const Matrix<T_, 2, 2>&) const;
	};

	template <typename T_, unsigned int size>
	struct calc_det<T_, size, size>
	{
		T_ operator()(const Matrix<T_, size, size>&) const;
	};

	template <typename T_, unsigned int rows_, unsigned int cols_>
	struct calc_inv
	{
		const Matrix<T_, rows_, cols_> operator()(const Matrix<T_, rows_, cols_>&) const;
	};

	template <typename T_>
	struct calc_inv<T_, 1, 1>
	{
		const Matrix<T_, 1, 1> operator()(const Matrix<T_, 1, 1>&) const;
	};

	template <typename T_>
	struct calc_inv<T_, 2, 2>
	{
		const Matrix<T_, 2, 2> operator()(const Matrix<T_, 2, 2>&) const;
	};

	template <typename T_, unsigned int size>
	struct calc_inv<T_, size, size>
	{
		const Matrix<T_, size, size> operator()(const Matrix<T_, size, size>&) const;
	};

	template <typename T_, unsigned int rows_, unsigned int cols_>
	struct calc_uptriag
	{
		bool operator()(const Matrix<T_, rows_, cols_>&) const;
	};

	template <typename T_, unsigned int size>
	struct calc_uptriag<T_, size, size>
	{
		bool operator()(const Matrix<T_, size, size>&) const;
	};

	template <typename T_, unsigned int rows_, unsigned int cols_>
	struct calc_lwtriag
	{
		bool operator()(const Matrix<T_, rows_, cols_>&) const;
	};

	template <typename T_, unsigned int size>
	struct calc_lwtriag<T_, size, size>
	{
		bool operator()(const Matrix<T_, size, size>&) const;
	};

public:
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<T>> list);
	std::array<T, cols> Getrow(unsigned int row) const;
	std::array<T, rows> Getcol(unsigned int col) const;
	T Getval(unsigned int row, unsigned int col) const;
	void Setval(unsigned int row, unsigned int col, T val);
	Matrix<T, cols, rows> Transpose() const;
	Matrix<T, rows, cols> operator+() const;
	Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols>& operand) const;
	Matrix<T, rows, cols>& operator+=(const Matrix<T, rows, cols>& operand);
	Matrix<T, rows, cols> operator-() const;
	Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols>& operand) const;
	Matrix<T, rows, cols>& operator-=(const Matrix<T, rows, cols>& operand);
	Matrix<T, rows, cols> operator*(T operand) const;
	Matrix<T, rows, cols>& operator*=(T operand);
	template <unsigned int opcols>
	Matrix<T, rows, opcols> operator*(const Matrix<T, cols, opcols>& operand) const;
	T Determinant() const;
	Matrix<T, rows, cols> Invert() const;
	template <typename T_, unsigned int rows_, unsigned int cols_>
	bool operator==(const Matrix<T_, rows_, cols_>& operand) const;
	template <typename T_, unsigned int rows_, unsigned int cols_>
	bool operator!=(const Matrix<T_, rows_, cols_>& operand) const;
	bool IsUpperTriangular() const;
	bool IsLowerTriangular() const;
	bool IsTriangular() const;
	bool IsDiagonal() const;

	virtual ~Matrix();
	// Additions
	void SetRow(unsigned int row, const std::array<T, cols>& data);
};

/* Identity matrix */
template <typename T, unsigned size>
Matrix<T, size, size> Identity()
{
	static_assert(size > 0, "Invalid size of matrix");
	Matrix<T, size, size> e;
	for (unsigned i = 0; i < size; i++)
		for (unsigned j = 0; j < size; j++)
			e.setval(i, j, i == j ? 1 : 0);
	return e;
}

MTXTMP
Matrix<T, rows, cols>::~Matrix() = default;

/* Default constructor */
MTXTMP
Matrix<T, rows, cols>::Matrix() : myVal({})
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
			myVal[row][col++] = *l;
		}
		++row;
	}
}

/* Row getter */
MTXTMP
std::array<T, cols> Matrix<T, rows, cols>::Getrow(unsigned int row) const
{
	return std::array<T, cols>(myVal[row]);
}

MTXTMP
void Matrix<T, rows, cols>::SetRow(unsigned int row, const std::array<T, cols>& data)
{
	myVal[row] = data;
}

/* Column getter */
MTXTMP
std::array<T, rows> Matrix<T, rows, cols>::Getcol(unsigned int col) const
{
	std::array<T, rows> ans;
	for (unsigned int i = 0; i < rows; i++)
		ans[i] = myVal[i][col];
	return ans;
}

/* Getter */
MTXTMP
T Matrix<T, rows, cols>::Getval(unsigned int row, unsigned int col) const
{
	return myVal[row][col];
}

/* Setter */
MTXTMP
void Matrix<T, rows, cols>::Setval(unsigned int row, unsigned int col, const T val)
{
	myVal[row][col] = val;
}

/* Transpose */
MTXTMP
Matrix<T, cols, rows> Matrix<T, rows, cols>::Transpose() const
{
	Matrix<T, cols, rows> ans;
	for (unsigned int i = 0; i < cols; i++)
		for (unsigned int j = 0; j < rows; j++)
			ans.Setval(i, j, myVal[j][i]);
	return ans;
}

/* Unary plus */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator+() const
{
	return *this;
}

/* Negation */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator-() const
{
	return (*this) * ((T)-1);
}

/* Addition */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator+(const Matrix<T, rows, cols>& operand) const
{
	Matrix<T, rows, cols> ans;
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			ans.myVal[i][j] = myVal[i][j] + operand.myVal[i][j];
	return ans;
}

MTXTMP
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator+=(const Matrix<T, rows, cols>& operand)
{
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			myVal[i][j] += operand.myVal[i][j];
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
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			myVal[i][j] -= operand.myVal[i][j];
	return *this;
}

/* Scalar multiplication */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::operator*(const T operand) const
{
	Matrix<T, rows, cols> ans;
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			ans.myVal[i][j] = myVal[i][j] * operand;
	return ans;
}

MTXTMP
Matrix<T, rows, cols>& Matrix<T, rows, cols>::operator*=(const T operand)
{
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < cols; j++)
			myVal[i][j] *= operand;
	return *this;
}

/* Matrix multiplication */
MTXTMP
template <unsigned int opcols>
Matrix<T, rows, opcols> Matrix<T, rows, cols>::operator*(const Matrix<T, cols, opcols>& operand) const
{
	Matrix<T, rows, opcols> ans = {};
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < opcols; j++)
		{
			for (unsigned int k = 0; k < cols; k++)
				ans.Setval(i, j, ans.Getval(i, j) + this->Getval(i, k) * operand.Getval(k, j));
		}
	}
	return ans;
}

/* Determinant (function object, error) */
MTXTMP
template <typename T_, unsigned int rows_, unsigned int cols_>
T_ Matrix<T, rows, cols>::calc_det<T_, rows_, cols_>::operator()(const Matrix<T_, rows_, cols_>&) const
{
	throw std::domain_error("Not a square matrix");
}

/* 1x1 matrix (in fact this is a scalar) determinant */
MTXTMP
template <typename T_>
T_ Matrix<T, rows, cols>::calc_det<T_, 1, 1>::operator()(const Matrix<T_, 1, 1>& arg) const
{
	return arg.getval(0, 0);
}

/* 2x2 matrix determinant */
MTXTMP
template <typename T_>
T_ Matrix<T, rows, cols>::calc_det<T_, 2, 2>::operator()(const Matrix<T_, 2, 2>& arg) const
{
	return arg.getval(0, 0) * arg.getval(1, 1) - arg.getval(0, 1) * arg.getval(1, 0);
}

/* nxn matrix determinant */
MTXTMP
template <typename T_, unsigned int size>
T_ Matrix<T, rows, cols>::calc_det<T_, size, size>::operator()(const Matrix<T_, size, size>& arg) const
{
	T_ det;
	if (arg.is_triangular())
	{
		det = T_(1);
		for (int i = 0; i < size; i++)
			det *= arg.getval(i, i);
	}
	else
	{
		Matrix<T_, size - 1, size - 1> minor;
		det = T_(0);
		for (int i = 0; i < size; i++)
		{
			for (int p = 0; p < size - 1; p++)
				for (int q = 1; q < size; q++)
					minor.setval(p, q - 1, arg.getval(p >= i ? p + 1 : p, q));
			if (i % 2 == 0)
				det += arg.getval(i, 0) * minor.determinant();
			else
				det -= arg.getval(i, 0) * minor.determinant();
		}
	}
	return det;
}

/* Determinant */
MTXTMP
T Matrix<T, rows, cols>::Determinant() const
{
	return calc_det<T, rows, cols>()(*this);
}

/* Invertion (function object, error) */
MTXTMP
template <typename T_, unsigned int rows_, unsigned int cols_>
const Matrix<T_, rows_, cols_>
Matrix<T, rows, cols>::calc_inv<T_, rows_, cols_>::operator()(const Matrix<T_, rows_, cols_>&) const
{
	throw std::domain_error("Not a square matrix");
}

/* 1x1 matrix (in fact this is a scalar) inversion */
MTXTMP
template <typename T_>
const Matrix<T_, 1, 1> Matrix<T, rows, cols>::calc_inv<T_, 1, 1>::operator()(const Matrix<T_, 1, 1>& arg) const
{
	T_ det = arg.determinant();
	if (det == T_(0)) throw std::domain_error("Cannot invert a singular matrix");
	return Matrix<T_, 1, 1>({
		{arg.getval(0, 0) / det,},
	});
}

/* 2x2 matrix inversion */
MTXTMP
template <typename T_>
const Matrix<T_, 2, 2> Matrix<T, rows, cols>::calc_inv<T_, 2, 2>::operator()(const Matrix<T_, 2, 2>& arg) const
{
	T_ det = arg.determinant();
	if (det == T_(0)) throw std::domain_error("Cannot invert a singular matrix");
	return Matrix<T_, 2, 2>({
		{arg.getval(1, 1) / det, -arg.getval(0, 1) / det,},
		{-arg.getval(0, 1) / det, arg.getval(0, 0) / det,},
	});
}

/* nxn matrix inversion */
MTXTMP
template <typename T_, unsigned int size>
const Matrix<T_, size, size>
Matrix<T, rows, cols>::calc_inv<T_, size, size>::operator()(const Matrix<T_, size, size>& arg) const
{
	Matrix<T_, size, size> inverse;
	Matrix<T_, size - 1, size - 1> minor;
	T_ det = arg.determinant();
	if (det == T_(0)) throw std::domain_error("Cannot invert a singular matrix");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int p = 0; p < size - 1; p++)
				for (int q = 0; q < size - 1; q++)
					minor.setval(p, q, arg.getval(p >= i ? p + 1 : p, q >= j ? q + 1 : q));
			if ((i + j) % 2 == 0)
				inverse.setval(j, i, minor.determinant() / det);
			else
				inverse.setval(j, i, -minor.determinant() / det);
		}
	}
	return inverse;
}

/* Inversion */
MTXTMP
Matrix<T, rows, cols> Matrix<T, rows, cols>::Invert() const
{
	return calc_inv<T, rows, cols>()(*this);
}

/* Equality */
MTXTMP
template <typename T_, unsigned int rows_, unsigned int cols_>
bool Matrix<T, rows, cols>::operator==(const Matrix<T_, rows_, cols_>& operand) const
{
	if (rows != rows_ || cols != cols_)
		return false;
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			if (myVal[i][j] != operand.getval(i, j))
				return false;
	return true;
}

/* Non-equality */
MTXTMP
template <typename T_, unsigned int rows_, unsigned int cols_>
bool Matrix<T, rows, cols>::operator!=(const Matrix<T_, rows_, cols_>& operand) const
{
	return !((*this) == operand);
}

/* is upper triangular? (function object, error) */
MTXTMP
template <typename T_, unsigned int rows_, unsigned int cols_>
bool Matrix<T, rows, cols>::calc_uptriag<T_, rows_, cols_>::operator()(const Matrix<T_, rows_, cols_>&) const
{
	throw std::domain_error("Not a square matrix");
}

/* is upper triangular? (function object, square) */
MTXTMP
template <typename T_, unsigned int size>
bool Matrix<T, rows, cols>::calc_uptriag<T_, size, size>::operator()(const Matrix<T_, size, size>& arg) const
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < i; j++)
			if (arg.getval(i, j) != T_(0))
				return false;
	return true;
}

/* is lower triangular? (function object, error) */
MTXTMP
template <typename T_, unsigned int rows_, unsigned int cols_>
bool Matrix<T, rows, cols>::calc_lwtriag<T_, rows_, cols_>::operator()(const Matrix<T_, rows_, cols_>&) const
{
	throw std::domain_error("Not a square matrix");
}

/* is lower triangular? (function object, square) */
MTXTMP
template <typename T_, unsigned int size>
bool Matrix<T, rows, cols>::calc_lwtriag<T_, size, size>::operator()(const Matrix<T_, size, size>& arg) const
{
	for (int i = 0; i < size; i++)
		for (int j = i + 1; j < size; j++)
			if (arg.getval(i, j) != T_(0))
				return false;
	return true;
}

/* is upper triangular? */
MTXTMP
bool Matrix<T, rows, cols>::IsUpperTriangular() const
{
	return calc_uptriag<T, rows, cols>()(*this);
}

/* is lower triangular? */
MTXTMP
bool Matrix<T, rows, cols>::IsLowerTriangular() const
{
	return calc_lwtriag<T, rows, cols>()(*this);
}

/* is triangular? */
MTXTMP
bool Matrix<T, rows, cols>::IsTriangular() const
{
	return IsUpperTriangular() || IsLowerTriangular();
}

/* is diagonal? */
MTXTMP
bool Matrix<T, rows, cols>::IsDiagonal() const
{
	return IsUpperTriangular() && IsLowerTriangular();
}

MTXTMP
std::ostream& operator<<(std::ostream& cout, const Matrix<T, rows, cols>& matrix)
{
	for (unsigned int row = 0; row < rows; ++row)
	{
		for(unsigned int col = 0; col < cols; ++col)
		{
			cout << std::setw(10) << matrix.Getval(row, col) << " ";
		}
		cout << std::endl;
	}

	return cout;
}

#endif
