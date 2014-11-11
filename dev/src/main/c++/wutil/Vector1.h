#ifndef _Vector1_h
#define _Vector1_h

// Vector1.h:
//
// This file defines one-component vectors and matrices.
//
// Control macros:
//
//	Vector1_NO_CHECKING	-- turn off range checking

#include <cmath>
#include <iostream>

class Matrix1;

class Vector1
{
public:
	Vector1(void);
	Vector1(const Vector1 &vector);
	~Vector1(void);
	Vector1 &operator=(const Vector1 &vector);
	Vector1 &zero(void);

	static int n_comps(void);
	static void range_check(int comp);

	double &operator()(int comp);
	double operator()(int comp) const;
	double &component(int comp);
	double component(int comp) const;

	Vector1 &operator*=(double s);
	Vector1 &operator+=(const Vector1 &b);
	Vector1 &operator-=(const Vector1 &b);

	class RangeViolation : public std::exception { };

private:
	double v1;

	Vector1(double v1_);

	friend inline Vector1 operator*(double s, const Vector1 &a);
	friend inline Vector1 operator+(const Vector1 &a, const Vector1 &b);
	friend inline Vector1 operator-(const Vector1 &a, const Vector1 &b);
	friend inline Vector1 operator*(const Matrix1 &matrix,
		const Vector1 &vector);
	friend inline double operator*(const Vector1 &a, const Vector1 &b);
	friend inline std::istream &operator>>(std::istream &is,
		Vector1 &vector);
	friend inline std::ostream &operator<<(std::ostream &os,
		const Vector1 &vector);
	friend class Matrix1;	// for row_vector() and column_vector()
};

inline Vector1 operator*(double s, const Vector1 &a);
inline Vector1 operator+(const Vector1 &a, const Vector1 &b);
inline Vector1 operator-(const Vector1 &a, const Vector1 &b);
inline double operator*(const Vector1 &a, const Vector1 &b);

inline std::istream &operator>>(std::istream &is, Vector1 &vector);
inline std::ostream &operator<<(std::ostream &os, const Vector1 &vector);

inline int
Vector1::n_comps(void)
{
	return 1;
}

#ifndef Vector1_NO_CHECKING

inline void
Vector1::range_check(int comp)
{
	if (comp < 0 || comp >= Vector1::n_comps())
		throw RangeViolation();
}

#else /* ! Vector1_NO_CHECKING */

inline void
Vector1::range_check(int /* comp */)
{
}

#endif /* Vector1_NO_CHECKING */

inline
Vector1::Vector1(void)
	: v1(0.)
{
}

inline
Vector1::Vector1(const Vector1 &vector)
	: v1(vector.v1)
{
}

inline
Vector1::Vector1(double v1_)
	: v1(v1_)
{
}

inline
Vector1::~Vector1(void)
{
}

inline Vector1 &
Vector1::operator=(const Vector1 &vector)
{
	v1 = vector.v1;
	return *this;
}

inline Vector1 &
Vector1::zero(void)
{
	v1 = 0.;
	return *this;
}

inline double &
Vector1::operator()(int comp)
{
	range_check(comp);
	return v1;
}

inline double
Vector1::operator()(int comp) const
{
	range_check(comp);
	return v1;
}

inline double &
Vector1::component(int comp)
{
	range_check(comp);
	return v1;
}

inline double
Vector1::component(int comp) const
{
	range_check(comp);
	return v1;
}

inline Vector1 &
Vector1::operator*=(double s)
{
	v1 *= s;
	return *this;
}

inline Vector1 &
Vector1::operator+=(const Vector1 &b)
{
	v1 += b.v1;
	return *this;
}

inline Vector1 &
Vector1::operator-=(const Vector1 &b)
{
	v1 -= b.v1;
	return *this;
}

inline Vector1
operator*(double s, const Vector1 &a)
{
	return Vector1(s*a.v1);
}

inline Vector1
operator+(const Vector1 &a, const Vector1 &b)
{
	return Vector1(a.v1 + b.v1);
}

inline Vector1
operator-(const Vector1 &a, const Vector1 &b)
{
	return Vector1(a.v1 - b.v1);
}

inline double
operator*(const Vector1 &a, const Vector1 &b)
{
	return a.v1*b.v1;
}

inline std::istream &
operator>>(std::istream &is, Vector1 &vector)
{
	is >> vector.v1;
	return is;
}

inline std::ostream &
operator<<(std::ostream &os, const Vector1 &vector)
{
	os << vector.v1;
	return os;
}

class Matrix1
{
public:
	Matrix1(void);
	Matrix1(const Matrix1 &matrix);
	~Matrix1(void);
	Matrix1 &operator=(const Matrix1 &matrix);
	Matrix1 &zero(void);

	static void range_check(int row, int col);

	double &operator()(int row, int col);
	double operator()(int row, int col) const;

	Vector1 row_vector(int i);
	Vector1 column_vector(int j);

	Matrix1 &operator*=(double s);
	Matrix1 &operator+=(const Matrix1 &b);
	Matrix1 &operator-=(const Matrix1 &b);

	Matrix1 &equals_multiple_of_identity(double s);
	Matrix1 &add_multiple_of_identity(double s);

	void eigen(Vector1 &evals, Matrix1 &evects);

	class RangeViolation : public std::exception { };

private:
	double e11;

	Matrix1(double e11_);

	friend inline Matrix1 operator*(double s, const Matrix1 &a);
	friend inline Matrix1 operator+(const Matrix1 &a, const Matrix1 &b);
	friend inline Matrix1 operator-(const Matrix1 &a, const Matrix1 &b);

	friend inline Vector1 operator*(const Matrix1 &matrix,
		const Vector1 &vector);
	friend inline Matrix1 operator*(const Matrix1 &a, const Matrix1 &b);
	friend inline Matrix1 inverse(const Matrix1 &matrix);
	friend inline Matrix1 transpose(const Matrix1 &matrix);
	friend inline Matrix1 deviator(const Matrix1 &matrix);
	friend double trace(const Matrix1 &matrix);
	friend double matrix_one_norm(const Matrix1 &matrix);
	friend double matrix_infinity_norm(const Matrix1 &matrix);
	friend inline std::istream &operator>>(std::istream &is,
		Matrix1 &matrix);
	friend inline std::ostream &operator<<(std::ostream &os,
		const Matrix1 &matrix);
};

inline Matrix1 operator*(double s, const Matrix1 &a);
inline Matrix1 operator+(const Matrix1 &a, const Matrix1 &b);
inline Matrix1 operator-(const Matrix1 &a, const Matrix1 &b);
inline Vector1 operator*(const Matrix1 &matrix, const Vector1 &vector);
inline Matrix1 operator*(const Matrix1 &a, const Matrix1 &b);

inline Matrix1 inverse(const Matrix1 &matrix);
inline Matrix1 transpose(const Matrix1 &matrix);
inline Matrix1 deviator(const Matrix1 &matrix);
inline double trace(const Matrix1 &matrix);

double matrix_one_norm(const Matrix1 &matrix);
double matrix_infinity_norm(const Matrix1 &matrix);

inline std::istream &operator>>(std::istream &is, Matrix1 &matrix);
inline std::ostream &operator<<(std::ostream &os, const Matrix1 &matrix);

#ifndef Vector1_NO_CHECKING

inline void
Matrix1::range_check(int row, int col)
{
	if (row < 0 || row >= Vector1::n_comps())
		throw RangeViolation();
	if (col < 0 || col >= Vector1::n_comps())
		throw RangeViolation();
}

#else /* ! Vector1_NO_CHECKING */

inline void
Matrix1::range_check(int /* row */, int /* col */)
{
}

#endif /* Vector1_NO_CHECKING */

inline
Matrix1::Matrix1(void)
	: e11(0.)
{
}

inline
Matrix1::Matrix1(const Matrix1 &matrix)
	: e11(matrix.e11)
{
}

inline
Matrix1::Matrix1(double e11_)
	: e11(e11_)
{
}

inline
Matrix1::~Matrix1(void)
{
}

inline Matrix1 &
Matrix1::operator=(const Matrix1 &matrix)
{
	e11 = matrix.e11;
	return *this;
}

inline Matrix1 &
Matrix1::zero(void)
{
	e11 = 0.;
	return *this;
}

inline double &
Matrix1::operator()(int row, int col)
{
	range_check(row, col);
	return e11;
}

inline double
Matrix1::operator()(int row, int col) const
{
	range_check(row, col);
	return e11;
}

inline Vector1
Matrix1::row_vector(int i)
{
	Vector1::range_check(i);
	return Vector1(e11);
}

inline Vector1
Matrix1::column_vector(int j)
{
	Vector1::range_check(j);
	return Vector1(e11);
}

inline Matrix1 &
Matrix1::operator*=(double s)
{
	e11 *= s;
	return *this;
}

inline Matrix1 &
Matrix1::operator+=(const Matrix1 &b)
{
	e11 += b.e11;
	return *this;
}

inline Matrix1 &
Matrix1::operator-=(const Matrix1 &b)
{
	e11 -= b.e11;
	return *this;
}

inline Matrix1 &
Matrix1::equals_multiple_of_identity(double s)
{
	e11 = s;
	return *this;
}

inline Matrix1 &
Matrix1::add_multiple_of_identity(double s)
{
	e11 += s;
	return *this;
}

inline void
Matrix1::eigen(Vector1 &evals, Matrix1 &evects)
{
	evals(0) = e11;
	evects(0,0) = 1.;
}

inline Matrix1
operator*(double s, const Matrix1 &a)
{
	return Matrix1(s*a.e11);
}

inline Matrix1
operator+(const Matrix1 &a, const Matrix1 &b)
{
	return Matrix1(a.e11 + b.e11);
}

inline Matrix1
operator-(const Matrix1 &a, const Matrix1 &b)
{
	return Matrix1(a.e11 - b.e11);
}

inline Vector1
operator*(const Matrix1 &matrix, const Vector1 &vector)
{
	return Vector1(matrix.e11*vector.v1);
}

inline Matrix1
operator*(const Matrix1 &a, const Matrix1 &b)
{
	return Matrix1(a.e11*b.e11);
}

inline Matrix1
inverse(const Matrix1 &matrix)
{
	return Matrix1(1./matrix.e11);
}

inline Matrix1
transpose(const Matrix1 &matrix)
{
	return Matrix1(matrix);
}

inline Matrix1
deviator(const Matrix1 & /* matrix */)
{
	Matrix1 M(0.);
	return M;
}

inline double
trace(const Matrix1 &matrix)
{
	return matrix.e11;
}

inline double
matrix_one_norm(const Matrix1 &matrix)
{
	double norm;
	norm = fabs(matrix.e11);
	return norm;
}

inline double
matrix_infinity_norm(const Matrix1 &matrix)
{
	double norm;
	norm = fabs(matrix.e11);
	return norm;
}

inline std::istream &
operator>>(std::istream &is, Matrix1 &matrix)
{
	is >> matrix.e11;
	return is;
}

inline std::ostream &
operator<<(std::ostream &os, const Matrix1 &matrix)
{
	os << matrix.e11 << "\n";
	return os;
}

class FactorMatrix1
{
public:
	FactorMatrix1(void);
	~FactorMatrix1(void);
	FactorMatrix1(const FactorMatrix1 &F);
	FactorMatrix1 &operator=(const FactorMatrix1 &F);

private:
	Matrix1 inverse;	// Unlike FactorMatrixN, FactorMatrix1 holds
				// inverse matrix only.

	FactorMatrix1(const Matrix1 &matrix);	// Copies matrix.
						// (It does not invert it.)

	friend FactorMatrix1 factor(const Matrix1 &matrix);
	friend Vector1 solve(const FactorMatrix1 &F, const Vector1 &vector);
	friend Matrix1 solve(const FactorMatrix1 &F, const Matrix1 &matrix);
	friend inline std::ostream &operator<<(std::ostream &os,
		const FactorMatrix1 &F);
};

FactorMatrix1 factor(const Matrix1 &matrix);
Vector1 solve(const FactorMatrix1 &F, const Vector1 &vector);
Matrix1 solve(const FactorMatrix1 &F, const Matrix1 &matrix);

inline std::ostream &operator<<(std::ostream &os, const FactorMatrix1 &F);

inline
FactorMatrix1::FactorMatrix1(void)
	: inverse()
{
}

inline
FactorMatrix1::~FactorMatrix1(void)
{
}

inline
FactorMatrix1::FactorMatrix1(const FactorMatrix1 &F)
	: inverse(F.inverse)
{
}

inline FactorMatrix1 &
FactorMatrix1::operator=(const FactorMatrix1 &F)
{
	inverse = F.inverse;
	return *this;
}

inline
FactorMatrix1::FactorMatrix1(const Matrix1 &matrix)
	: inverse(matrix)
{
}

inline FactorMatrix1
factor(const Matrix1 &matrix)
{
	return FactorMatrix1(::inverse(matrix));
}

inline Vector1
solve(const FactorMatrix1 &F, const Vector1 &vector)
{
	return F.inverse * vector;
}

inline Matrix1
solve(const FactorMatrix1 &F, const Matrix1 &matrix)
{
	return F.inverse * matrix;
}

inline std::ostream &
operator<<(std::ostream &os, const FactorMatrix1 &F)
{
	os << F.inverse;
	return os;
}

#endif /* _Vector1_h */
