#ifndef _Vector2_h
#define _Vector2_h

// Vector2.h:
//
// This file defines two-component vectors and matrices.
//
// Control macros:
//
//	Vector2_NO_CHECKING	-- turn off range checking

#include <cmath>
#include <iostream>
#include "eigen.h"

class Matrix2;

class Vector2
{
public:
	Vector2(void);
	Vector2(const Vector2 &vector);
	~Vector2(void);
	Vector2 &operator=(const Vector2 &vector);
	Vector2 &zero(void);

	static int n_comps(void);
	static void range_check(int comp);

	double &operator()(int comp);
	double operator()(int comp) const;
	double &component(int comp);
	double component(int comp) const;

	Vector2 &operator*=(double s);
	Vector2 &operator+=(const Vector2 &b);
	Vector2 &operator-=(const Vector2 &b);

	class RangeViolation : public std::exception { };

private:
	double v1, v2;

	Vector2(double v1_, double v2_);

	friend inline Vector2 operator*(double s, const Vector2 &a);
	friend inline Vector2 operator+(const Vector2 &a, const Vector2 &b);
	friend inline Vector2 operator-(const Vector2 &a, const Vector2 &b);
	friend inline Vector2 operator*(const Matrix2 &matrix,
		const Vector2 &vector);
	friend inline double operator*(const Vector2 &a, const Vector2 &b);
	friend inline std::istream &operator>>(std::istream &is,
		Vector2 &vector);
	friend inline std::ostream &operator<<(std::ostream &os,
		const Vector2 &vector);
	friend class Matrix2;	// for row_vector() and column_vector()
};

inline Vector2 operator*(double s, const Vector2 &a);
inline Vector2 operator+(const Vector2 &a, const Vector2 &b);
inline Vector2 operator-(const Vector2 &a, const Vector2 &b);
inline double operator*(const Vector2 &a, const Vector2 &b);

inline std::istream &operator>>(std::istream &is, Vector2 &vector);
inline std::ostream &operator<<(std::ostream &os, const Vector2 &vector);

inline int
Vector2::n_comps(void)
{
	return 2;
}

#ifndef Vector2_NO_CHECKING

inline void
Vector2::range_check(int comp)
{
	if (comp < 0 || comp >= Vector2::n_comps())
		throw RangeViolation();
}

#else /* ! Vector2_NO_CHECKING */

inline void
Vector2::range_check(int /* comp */)
{
}

#endif /* Vector2_NO_CHECKING */

inline
Vector2::Vector2(void)
	: v1(0.),
	  v2(0.)
{
}

inline
Vector2::Vector2(const Vector2 &vector)
	: v1(vector.v1),
	  v2(vector.v2)
{
}

inline
Vector2::Vector2(double v1_, double v2_)
	: v1(v1_),
	  v2(v2_)
{
}

inline
Vector2::~Vector2(void)
{
}

inline Vector2 &
Vector2::operator=(const Vector2 &vector)
{
	v1 = vector.v1;
	v2 = vector.v2;
	return *this;
}

inline Vector2 &
Vector2::zero(void)
{
	v1 = 0.;
	v2 = 0.;
	return *this;
}

inline double &
Vector2::operator()(int comp)
{
	range_check(comp);
	return (comp == 0) ? v1 : v2;
}

inline double
Vector2::operator()(int comp) const
{
	range_check(comp);
	return (comp == 0) ? v1 : v2;
}

inline double &
Vector2::component(int comp)
{
	range_check(comp);
	return (comp == 0) ? v1 : v2;
}

inline double
Vector2::component(int comp) const
{
	range_check(comp);
	return (comp == 0) ? v1 : v2;
}

inline Vector2 &
Vector2::operator*=(double s)
{
	v1 *= s;
	v2 *= s;
	return *this;
}

inline Vector2 &
Vector2::operator+=(const Vector2 &b)
{
	v1 += b.v1;
	v2 += b.v2;
	return *this;
}

inline Vector2 &
Vector2::operator-=(const Vector2 &b)
{
	v1 -= b.v1;
	v2 -= b.v2;
	return *this;
}

inline Vector2
operator*(double s, const Vector2 &a)
{
	return Vector2(s*a.v1, s*a.v2);
}

inline Vector2
operator+(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.v1 + b.v1, a.v2 + b.v2);
}

inline Vector2
operator-(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.v1 - b.v1, a.v2 - b.v2);
}

inline double
operator*(const Vector2 &a, const Vector2 &b)
{
	return a.v1*b.v1 + a.v2*b.v2;
}

inline std::istream &
operator>>(std::istream &is, Vector2 &vector)
{
	is >> vector.v1 >> vector.v2;
	return is;
}

inline std::ostream &
operator<<(std::ostream &os, const Vector2 &vector)
{
	os << vector.v1 << " " << vector.v2;
	return os;
}

class Matrix2
{
public:
	Matrix2(void);
	Matrix2(const Matrix2 &matrix);
	~Matrix2(void);
	Matrix2 &operator=(const Matrix2 &matrix);
	Matrix2 &zero(void);

	static void range_check(int row, int col);

	double &operator()(int row, int col);
	double operator()(int row, int col) const;

	Vector2 row_vector(int i);
	Vector2 column_vector(int j);

	Matrix2 &operator*=(double s);
	Matrix2 &operator+=(const Matrix2 &b);
	Matrix2 &operator-=(const Matrix2 &b);

	Matrix2 &equals_multiple_of_identity(double s);
	Matrix2 &add_multiple_of_identity(double s);

	void eigen(Vector2 &evals, Matrix2 &evects);

	class RangeViolation : public std::exception { };

private:
	double e11, e12, e21, e22;

	Matrix2(double e11_, double e12_, double e21_, double e22_);

	friend inline Matrix2 operator*(double s, const Matrix2 &a);
	friend inline Matrix2 operator+(const Matrix2 &a, const Matrix2 &b);
	friend inline Matrix2 operator-(const Matrix2 &a, const Matrix2 &b);
	friend inline Vector2 operator*(const Matrix2 &matrix,
		const Vector2 &vector);
	friend inline Matrix2 operator*(const Matrix2 &a, const Matrix2 &b);
	friend inline Matrix2 inverse(const Matrix2 &matrix);
	friend inline Matrix2 transpose(const Matrix2 &matrix);
	friend inline Matrix2 deviator(const Matrix2 &matrix);
	friend double trace(const Matrix2 &matrix);
	friend double matrix_one_norm(const Matrix2 &matrix);
	friend double matrix_infinity_norm(const Matrix2 &matrix);
	friend inline std::istream &operator>>(std::istream &is,
		Matrix2 &matrix);
	friend inline std::ostream &operator<<(std::ostream &os,
		const Matrix2 &matrix);
};

inline Matrix2 operator*(double s, const Matrix2 &a);
inline Matrix2 operator+(const Matrix2 &a, const Matrix2 &b);
inline Matrix2 operator-(const Matrix2 &a, const Matrix2 &b);
inline Vector2 operator*(const Matrix2 &matrix, const Vector2 &vector);
inline Matrix2 operator*(const Matrix2 &a, const Matrix2 &b);

inline Matrix2 inverse(const Matrix2 &matrix);
inline Matrix2 transpose(const Matrix2 &matrix);
inline double trace(const Matrix2 &matrix);

double matrix_one_norm(const Matrix2 &matrix);
double matrix_infinity_norm(const Matrix2 &matrix);

inline std::istream &operator>>(std::istream &is, Matrix2 &matrix);
inline std::ostream &operator<<(std::ostream &os, const Matrix2 &matrix);

#ifndef Vector2_NO_CHECKING

inline void
Matrix2::range_check(int row, int col)
{
	if (row < 0 || row >= Vector2::n_comps())
		throw RangeViolation();
	if (col < 0 || col >= Vector2::n_comps())
		throw RangeViolation();
}

#else /* ! Vector2_NO_CHECKING */

inline void
Matrix2::range_check(int /* row */, int /* col */)
{
}

#endif /* Vector2_NO_CHECKING */

inline
Matrix2::Matrix2(void)
	: e11(0.),
	  e12(0.),
	  e21(0.),
	  e22(0.)
{
}

inline
Matrix2::Matrix2(const Matrix2 &matrix)
	: e11(matrix.e11),
	  e12(matrix.e12),
	  e21(matrix.e21),
	  e22(matrix.e22)
{
}

inline
Matrix2::Matrix2(double e11_, double e12_, double e21_, double e22_)
	: e11(e11_),
	  e12(e12_),
	  e21(e21_),
	  e22(e22_)
{
}

inline
Matrix2::~Matrix2(void)
{
}

inline Matrix2 &
Matrix2::operator=(const Matrix2 &matrix)
{
	e11 = matrix.e11;
	e12 = matrix.e12;
	e21 = matrix.e21;
	e22 = matrix.e22;
	return *this;
}

inline Matrix2 &
Matrix2::zero(void)
{
	e11 = 0.;
	e12 = 0.;
	e21 = 0.;
	e22 = 0.;
	return *this;
}

inline Vector2
Matrix2::row_vector(int i)
{
	Vector2::range_check(i);
	return (i == 0) ? Vector2(e11, e12) : Vector2(e21, e22);
}

inline Vector2
Matrix2::column_vector(int j)
{
	Vector2::range_check(j);
	return (j == 0) ? Vector2(e11, e21) : Vector2(e12, e22);
}

inline Matrix2 &
Matrix2::operator*=(double s)
{
	e11 *= s;
	e12 *= s;
	e21 *= s;
	e22 *= s;
	return *this;
}

inline Matrix2 &
Matrix2::operator+=(const Matrix2 &b)
{
	e11 += b.e11;
	e12 += b.e12;
	e21 += b.e21;
	e22 += b.e22;
	return *this;
}

inline Matrix2 &
Matrix2::operator-=(const Matrix2 &b)
{
	e11 -= b.e11;
	e12 -= b.e12;
	e21 -= b.e21;
	e22 -= b.e22;
	return *this;
}

inline Matrix2 &
Matrix2::equals_multiple_of_identity(double s)
{
	e11 = s;
	e12 = 0.;
	e21 = 0.;
	e22 = s;
	return *this;
}

inline Matrix2 &
Matrix2::add_multiple_of_identity(double s)
{
	e11 += s;
	e22 += s;
	return *this;
}

inline Matrix2
operator*(double s, const Matrix2 &a)
{
	return Matrix2(s*a.e11, s*a.e12,
		       s*a.e21, s*a.e22);
}

inline Matrix2
operator+(const Matrix2 &a, const Matrix2 &b)
{
	return Matrix2(a.e11 + b.e11, a.e12 + b.e12,
		       a.e21 + b.e21, a.e22 + b.e22);
}

inline Matrix2
operator-(const Matrix2 &a, const Matrix2 &b)
{
	return Matrix2(a.e11 - b.e11, a.e12 - b.e12,
		       a.e21 - b.e21, a.e22 - b.e22);
}

inline Vector2
operator*(const Matrix2 &matrix, const Vector2 &vector)
{
	return Vector2(matrix.e11*vector.v1 + matrix.e12*vector.v2,
		       matrix.e21*vector.v1 + matrix.e22*vector.v2);
}

inline Matrix2
operator*(const Matrix2 &a, const Matrix2 &b)
{
	return Matrix2(a.e11*b.e11 + a.e12*b.e21, a.e11*b.e12 + a.e12*b.e22,
		       a.e21*b.e11 + a.e22*b.e21, a.e21*b.e12 + a.e22*b.e22);
}

inline Matrix2
inverse(const Matrix2 &matrix)
{
	double invdet = 1./(matrix.e11*matrix.e22 - matrix.e12*matrix.e21);
	return Matrix2( invdet*matrix.e22, -invdet*matrix.e12,
		       -invdet*matrix.e21,  invdet*matrix.e11);
}

inline Matrix2
transpose(const Matrix2 &matrix)
{
	return Matrix2(matrix.e11, matrix.e21, matrix.e12, matrix.e22);
}

inline Matrix2
deviator(const Matrix2 &matrix)
{
	Matrix2 M(matrix);
	M.add_multiple_of_identity(-.5*trace(M));
	return M;
}

inline double
trace(const Matrix2 &matrix)
{
	return matrix.e11 + matrix.e22;
}

inline double
matrix_one_norm(const Matrix2 &matrix)
{
	double norm1, norm2;
	norm1 = fabs(matrix.e11) + fabs(matrix.e21);
	norm2 = fabs(matrix.e12) + fabs(matrix.e22);
	return (norm1 >= norm2 ? norm1 : norm2);
}

inline double
matrix_infinity_norm(const Matrix2 &matrix)
{
	double norm1, norm2;
	norm1 = fabs(matrix.e11) + fabs(matrix.e12);
	norm2 = fabs(matrix.e21) + fabs(matrix.e22);
	return (norm1 >= norm2 ? norm1 : norm2);
}

inline std::istream &
operator>>(std::istream &is, Matrix2 &matrix)
{
	is >> matrix.e11 >> matrix.e12 >> matrix.e21 >> matrix.e22;
	return is;
}

inline std::ostream &
operator<<(std::ostream &os, const Matrix2 &matrix)
{
	os << matrix.e11 << " " << matrix.e12 << "\n";
	os << matrix.e21 << " " << matrix.e22 << "\n";
	return os;
}

class FactorMatrix2
{
public:
	FactorMatrix2(void);
	~FactorMatrix2(void);
	FactorMatrix2(const FactorMatrix2 &F);
	FactorMatrix2 &operator=(const FactorMatrix2 &F);

private:
	Matrix2 inverse;	// Unlike FactorMatrixN, FactorMatrix2 holds
				// inverse matrix only.

	FactorMatrix2(const Matrix2 &matrix);	// Copies matrix.
						// (It does not invert it.)

	friend FactorMatrix2 factor(const Matrix2 &matrix);
	friend Vector2 solve(const FactorMatrix2 &F, const Vector2 &vector);
	friend Matrix2 solve(const FactorMatrix2 &F, const Matrix2 &matrix);
	friend inline std::ostream &operator<<(std::ostream &os,
		const FactorMatrix2 &F);
};

FactorMatrix2 factor(const Matrix2 &matrix);
Vector2 solve(const FactorMatrix2 &F, const Vector2 &vector);
Matrix2 solve(const FactorMatrix2 &F, const Matrix2 &matrix);

inline std::ostream &operator<<(std::ostream &os, const FactorMatrix2 &F);

inline
FactorMatrix2::FactorMatrix2(void)
	: inverse()
{
}

inline
FactorMatrix2::~FactorMatrix2(void)
{
}

inline
FactorMatrix2::FactorMatrix2(const FactorMatrix2 &F)
	: inverse(F.inverse)
{
}

inline FactorMatrix2 &
FactorMatrix2::operator=(const FactorMatrix2 &F)
{
	inverse = F.inverse;
	return *this;
}

inline
FactorMatrix2::FactorMatrix2(const Matrix2 &matrix)
	: inverse(matrix)
{
}

inline FactorMatrix2
factor(const Matrix2 &matrix)
{
	return FactorMatrix2(::inverse(matrix));
}

inline Vector2
solve(const FactorMatrix2 &F, const Vector2 &vector)
{
	return F.inverse * vector;
}

inline Matrix2
solve(const FactorMatrix2 &F, const Matrix2 &matrix)
{
	return F.inverse * matrix;
}

inline std::ostream &
operator<<(std::ostream &os, const FactorMatrix2 &F)
{
	os << F.inverse;
	return os;
}

#endif /* _Vector2_h */
