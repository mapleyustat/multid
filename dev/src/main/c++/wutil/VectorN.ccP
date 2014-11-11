#include <cmath>

std::istream &
operator>>(std::istream &is, VectorN &vector)
{
	for (int i = 0; i < VectorN_N_COMPS; i++)
		is >> vector(i);
	return is;
}

std::ostream &
operator<<(std::ostream &os, const VectorN &vector)
{
	os << vector(0);
	for (int i = 1; i < VectorN_N_COMPS; i++)
		os << " " << vector(i);
	return os;
}

double &
MatrixN::operator()(int row, int col)
{
	range_check(row, col);
	return m[row][col];
}

double
MatrixN::operator()(int row, int col) const
{
	range_check(row, col);
	return m[row][col];
}

VectorN
MatrixN::row_vector(int i)
{
	VectorN::range_check(i);
	VectorN row_vec;
	for (int j = 0; j < VectorN_N_COMPS; j++)
		row_vec.v[j] = m[i][j];
	return row_vec;
}

VectorN
MatrixN::column_vector(int j)
{
	VectorN::range_check(j);
	VectorN column_vec;
	for (int i = 0; i < VectorN_N_COMPS; i++)
		column_vec.v[i] = m[i][j];
	return column_vec;
}

void
MatrixN::eigen(VectorN & /* evals */, MatrixN & /* evects */)
{
	std::cerr << "MatrixN::eigen() not yet implemented\n";
	throw NotImplemented();
}

MatrixN
inverse(const MatrixN &matrix)
{
	FactorMatrixN F(factor(matrix));
	VectorN col;
	MatrixN inv;
	for (int j = 0; j < VectorN_N_COMPS; j++) {
		int i;
		for (i = 0; i < VectorN_N_COMPS; i++)
			col(i) = 0.0;
		col(j) = 1.0;
		VectorN g(solve(F, col));
		for (i = 0; i < VectorN_N_COMPS; i++)
			inv(i,j) = g(i);
	}
	return inv;
}

MatrixN
transpose(const MatrixN &matrix)
{
	MatrixN T;
	for (int i = 0; i < VectorN_N_COMPS; i++)
		for (int j = 0; j < VectorN_N_COMPS; j++)
			 T(j,i) = matrix(i,j);
	return T;
}

MatrixN
deviator(const MatrixN &matrix)
{
	MatrixN M(matrix);
	M.add_multiple_of_identity(-trace(M)/VectorN_N_COMPS);
	return M;
}

double
trace(const MatrixN &matrix)
{
	double trace = matrix(0,0);
	for (int i = 1; i < VectorN_N_COMPS; i++)
		trace += matrix(i,i);
	return trace;
}

inline double
max(const double* norm) // Given a set of positive numbers, finds the maximum.
			// Used by matrix norms.
{
	double max_value = norm[0];
	for (int i = 1; i < VectorN_N_COMPS; i++) {
		if (max_value < norm[i])
			max_value = norm[i];
	}
	return max_value;
}

double
matrix_one_norm(const MatrixN &matrix)
{
	double norm[VectorN_N_COMPS];

	for (int i = 0; i < VectorN_N_COMPS; i++)
		norm[i] = 0.0;
	for (int j = 0; j < VectorN_N_COMPS; j++)
		for (int i = 0; i < VectorN_N_COMPS; i++)
			norm[j] += fabs(matrix(i,j));
	return max(norm);
}

double
matrix_infinity_norm(const MatrixN &matrix)
{
	double norm[VectorN_N_COMPS];

	int i;
	for (i = 0; i < VectorN_N_COMPS; i++)
		norm[i] = 0.0;
	for (i = 0; i < VectorN_N_COMPS; i++)
		for (int j = 0; j < VectorN_N_COMPS; j++)
			norm[i] += fabs(matrix(i,j));
	return max(norm);
}

std::istream &
operator>>(std::istream &is, MatrixN &matrix)
{
	int i, j;
	for (i = 0; i < VectorN_N_COMPS; i++)
		for (j = 0; j < VectorN_N_COMPS; j++)
			is >> matrix(i, j);
	return is;
}

std::ostream &
operator<<(std::ostream &os, const MatrixN &matrix)
{
	int i, j;
	for (i = 0; i < VectorN_N_COMPS; i++) {
		for (j = 0; j < VectorN_N_COMPS; j++)
			os << matrix(i, j) << " ";
		os << "\n";
	}
	return os;
}

// The code for factor() and solve() come from
//
// Numerical Recipes in C.
// Press, Teukolsky, Vetterling and Flannery.
// Cambridge University Press.
// ISBN: 0-521-43108-5

#define TINY 1.0e-30;

FactorMatrixN
factor(const MatrixN &matrix)	// This is ludcmp in Numerical Recipes.
{
	FactorMatrixN F;
	F.lu_ = matrix;
	MatrixN &lu = F.lu_;

	int i, imax, j, k;	// ludcmp starts here.
	int index[VectorN_N_COMPS];
	double max, dum, sum, temp;
	double vv[VectorN_N_COMPS];

	for (i = 0; i < VectorN_N_COMPS; i++) {
		max = 0.0;
		for (j = 0; j < VectorN_N_COMPS; j++)
			if ((temp = fabs(lu(i,j))) > max)
				max = temp;
		if (max == 0.0)
			std::cerr << "Singular matrix in routine solve" << "\n";
		vv[i] = 1.0 / max;
	}

	for (j = 0; j < VectorN_N_COMPS; j++) {
		for (i = 0; i < j; i++) {
			sum = lu(i,j);
			for (k = 0; k < i; k++)
				sum -= lu(i,k) * lu(k,j);
			lu(i,j) = sum;
		}
		max = 0.0;
#ifdef __GNUC__
		imax = j;	// avoid compiler warning
#endif
		for (i = j; i < VectorN_N_COMPS; i++) {
			sum = lu(i,j);
			for (k = 0; k < j; k++)
				sum -= lu(i,k) * lu(k,j);
			lu(i,j) = sum;
			if ((dum = vv[i] * fabs(sum)) >= max) {
				max = dum;
				imax = i;
			}
		}
		if (j != imax) {
			for (k = 0; k < VectorN_N_COMPS; k++) {
				dum = lu(imax,k);
				lu(imax,k) = lu(j,k);
				lu(j,k) = dum;
			}
			vv[imax] = vv[j];
		}
		index[j] = imax;
		if (lu(j,j) == 0.0)
			lu(j,j) = TINY;
		if (j != VectorN_N_COMPS - 1) {
			dum = 1.0 / lu(j,j);
			for (i = j+1; i < VectorN_N_COMPS; i++)
				lu(i,j) *= dum;
		}
	}

	for (i = 0; i < VectorN_N_COMPS; i++)
		F.index_[i] = index[i];
	return F;
}

VectorN
solve(const FactorMatrixN &F, const VectorN &vector)	// This is lubksb in
							// Numerical Recipes.
{
	VectorN bvector(vector);
	const MatrixN &lu = F.lu_;
	int i, ii = -1, ip, j;	// lubksb starts here.
	double sum;

	for (i = 0; i < VectorN_N_COMPS; i++) {
		ip = F.index_[i];
		sum = bvector(ip);
		bvector(ip) = bvector(i);
		if (ii != -1)
			for (j = ii; j <= i - 1; j++)
				 sum -= lu(i,j) * bvector(j);
		else if (sum)
			ii = i;
		bvector(i) = sum;
	}

	for (i = VectorN_N_COMPS - 1; i >= 0; i--) {
		sum = bvector(i);
		for (j = i + 1; j < VectorN_N_COMPS; j++)
			sum -= lu(i,j) * bvector(j);
		bvector(i) = sum / lu(i,i);
	}
	return bvector;
}

MatrixN
solve(const FactorMatrixN &F, const MatrixN &matrix)
{
	int i, j;
	MatrixN tmx1(matrix);
	MatrixN tmx2;
	VectorN tvec1;
	for (j = 0; j < VectorN_N_COMPS; j++) {
		for (i = 0; i < VectorN_N_COMPS; i++)
			tvec1(i) = tmx1(i,j);
		VectorN tvec2(solve(F, tvec1));
		for (i = 0; i < VectorN_N_COMPS; i++)
			tmx2(i,j) = tvec2(i);
	}
	return tmx2;
}

std::ostream &
operator<<(std::ostream &os, const FactorMatrixN &F)
{
	os << F.lu_;
	for (int i = 0; i < VectorN_N_COMPS; i++)
		os << F.index_[i] << " ";
	os << "\n";
	return os;
}
