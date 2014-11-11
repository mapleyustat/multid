#include "Vector3.h"

Vector3::~Vector3(void)
{
}

double &
Vector3::operator()(int comp)
{
	range_check(comp);
	return (comp == 0) ? v1 : ( (comp == 1) ? v2 : v3 );
}

double
Vector3::operator()(int comp) const
{
	range_check(comp);
	return (comp == 0) ? v1 : ( (comp == 1) ? v2 : v3 );
}

double &
Vector3::component(int comp)
{
	range_check(comp);
	return (comp == 0) ? v1 : ( (comp == 1) ? v2 : v3 );
}

double
Vector3::component(int comp) const
{
	range_check(comp);
	return (comp == 0) ? v1 : ( (comp == 1) ? v2 : v3 );
}

double &
Matrix3::operator()(int row, int col)
{
	range_check(row, col);
	return (row == 0) ? ((col == 0) ? e11 : ((col == 1) ? e12 : e13))
		: ((row == 1) ? ((col == 0) ? e21 : ((col == 1) ? e22 : e23))
			: ((col == 0) ? e31 : ((col == 1) ? e32 : e33)));

}

double
Matrix3::operator()(int row, int col) const
{
	range_check(row, col);
	return (row == 0) ? ((col == 0) ? e11 : ((col == 1) ? e12 : e13))
		: ((row == 1) ? ((col == 0) ? e21 : ((col == 1) ? e22 : e23))
			: ((col == 0) ? e31 : ((col == 1) ? e32 : e33)));

}

Matrix3 &
Matrix3::operator*=(double s)
{
	e11 *= s;
	e12 *= s;
	e13 *= s;
	e21 *= s;
	e22 *= s;
	e23 *= s;
	e31 *= s;
	e32 *= s;
	e33 *= s;
	return *this;
}

Matrix3 &
Matrix3::operator+=(const Matrix3 &b)
{
	e11 += b.e11;
	e12 += b.e12;
	e13 += b.e13;
	e21 += b.e21;
	e22 += b.e22;
	e23 += b.e23;
	e31 += b.e31;
	e32 += b.e32;
	e33 += b.e33;
	return *this;
}

Matrix3 &
Matrix3::operator-=(const Matrix3 &b)
{
	e11 -= b.e11;
	e12 -= b.e12;
	e13 -= b.e13;
	e21 -= b.e21;
	e22 -= b.e22;
	e23 -= b.e23;
	e31 -= b.e31;
	e32 -= b.e32;
	e33 -= b.e33;
	return *this;
}

Matrix3
operator*(double s, const Matrix3 &a)
{
	return Matrix3(s*a.e11, s*a.e12, s*a.e13,
		       s*a.e21, s*a.e22, s*a.e23,
		       s*a.e31, s*a.e32, s*a.e33);
}

Matrix3
operator+(const Matrix3 &a, const Matrix3 &b)
{
	return Matrix3(a.e11 + b.e11, a.e12 + b.e12, a.e13 + b.e13,
		       a.e21 + b.e21, a.e22 + b.e22, a.e23 + b.e23,
		       a.e31 + b.e31, a.e32 + b.e32, a.e33 + b.e33);
}

Matrix3
operator-(const Matrix3 &a, const Matrix3 &b)
{
	return Matrix3(a.e11 - b.e11, a.e12 - b.e12, a.e13 - b.e13,
		       a.e21 - b.e21, a.e22 - b.e22, a.e23 - b.e23,
		       a.e31 - b.e31, a.e32 - b.e32, a.e33 - b.e33);
}

Vector3
operator*(const Matrix3 &matrix, const Vector3 &vector)
{
	return Vector3(
	 matrix.e11*vector.v1 + matrix.e12*vector.v2 + matrix.e13*vector.v3,
	 matrix.e21*vector.v1 + matrix.e22*vector.v2 + matrix.e23*vector.v3,
	 matrix.e31*vector.v1 + matrix.e32*vector.v2 + matrix.e33*vector.v3);
}

Matrix3
operator*(const Matrix3 &a, const Matrix3 &b)
{
	return Matrix3(a.e11*b.e11 + a.e12*b.e21 + a.e13*b.e31,
		a.e11*b.e12 + a.e12*b.e22 + a.e13*b.e32,
		a.e11*b.e13 + a.e12*b.e23 + a.e13*b.e33,
		a.e21*b.e11 + a.e22*b.e21 + a.e23*b.e31,
		a.e21*b.e12 + a.e22*b.e22 + a.e23*b.e32,
		a.e21*b.e13 + a.e22*b.e23 + a.e23*b.e33,
		a.e31*b.e11 + a.e32*b.e21 + a.e33*b.e31,
		a.e31*b.e12 + a.e32*b.e22 + a.e33*b.e32,
		a.e31*b.e13 + a.e32*b.e23 + a.e33*b.e33);
}

Matrix3
inverse(const Matrix3 &matrix)
{
	double invdet = 1./(matrix.e11*matrix.e22*matrix.e33
		+ matrix.e12*matrix.e23*matrix.e31
		+ matrix.e13*matrix.e21*matrix.e32
		- (matrix.e13*matrix.e22*matrix.e31
		+ matrix.e23*matrix.e32*matrix.e11
		+ matrix.e33*matrix.e12*matrix.e21));
	return Matrix3( invdet*(matrix.e22*matrix.e33-matrix.e23*matrix.e32),
		       -invdet*(matrix.e12*matrix.e33-matrix.e13*matrix.e32),
			invdet*(matrix.e12*matrix.e23-matrix.e13*matrix.e22),
		       -invdet*(matrix.e21*matrix.e33-matrix.e23*matrix.e31),
			invdet*(matrix.e11*matrix.e33-matrix.e13*matrix.e31),
		       -invdet*(matrix.e11*matrix.e23-matrix.e13*matrix.e21),
			invdet*(matrix.e21*matrix.e32-matrix.e22*matrix.e31),
		       -invdet*(matrix.e11*matrix.e32-matrix.e12*matrix.e31),
			invdet*(matrix.e11*matrix.e22-matrix.e12*matrix.e21) );
}

double
matrix_one_norm(const Matrix3 &matrix)
{
	double norm1, norm2, norm3;
	norm1 = fabs(matrix.e11) + fabs(matrix.e21) + fabs(matrix.e31);
	norm2 = fabs(matrix.e12) + fabs(matrix.e22) + fabs(matrix.e32);
	norm3 = fabs(matrix.e13) + fabs(matrix.e23) + fabs(matrix.e33);
	norm1 = (norm1 >= norm2) ? norm1 : norm2;
	norm1 = (norm1 >= norm3) ? norm1 : norm3;
	return norm1;
}

double
matrix_infinity_norm(const Matrix3 &matrix)
{
	double norm1, norm2, norm3;
	norm1 = fabs(matrix.e11) + fabs(matrix.e12) + fabs(matrix.e13);
	norm2 = fabs(matrix.e21) + fabs(matrix.e22) + fabs(matrix.e23);
	norm3 = fabs(matrix.e31) + fabs(matrix.e32) + fabs(matrix.e33);
	norm1 = (norm1 >= norm2) ? norm1 : norm2;
	norm1 = (norm1 >= norm3) ? norm1 : norm3;
	return norm1;
}

std::istream &
operator>>(std::istream &is, Matrix3 &matrix)
{
	is >> matrix.e11 >> matrix.e12 >> matrix.e13;
	is >> matrix.e21 >> matrix.e22 >> matrix.e23;
	is >> matrix.e31 >> matrix.e32 >> matrix.e33;
	return is;
}

std::ostream &
operator<<(std::ostream &os, const Matrix3 &matrix)
{
	os << matrix.e11 << " " << matrix.e12 << " " << matrix.e13 << "\n";
	os << matrix.e21 << " " << matrix.e22 << " " << matrix.e23 << "\n";
	os << matrix.e31 << " " << matrix.e32 << " " << matrix.e33 << "\n";
	return os;
}
