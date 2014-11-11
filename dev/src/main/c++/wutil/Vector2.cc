#include "Vector2.h"

double &
Matrix2::operator()(int row, int col)
{
	range_check(row, col);
	return (row == 0) ? ((col == 0) ? e11 : e12)
			   : ((col == 0) ? e21 : e22);
}

double
Matrix2::operator()(int row, int col) const
{
	range_check(row, col);
	return (row == 0) ? ((col == 0) ? e11 : e12)
			   : ((col == 0) ? e21 : e22);
}

void
Matrix2::eigen(Vector2 &evals, Matrix2 &evects)
{
	double lambda[2];
	double matrix[2][2];
	double rvect[2];
	double lvect[2];

	matrix[0][0] = e11;
	matrix[0][1] = e12;
	matrix[1][0] = e21;
	matrix[1][1] = e22;

	int num_real_roots = eigval(lambda, matrix);
	evals(0) = lambda[0];
	evals(1) = lambda[1];

	int family = 0;
	rlvect(rvect, lvect, family, matrix, lambda, num_real_roots);
	evects(0,0) = rvect[0];
	evects(1,0) = rvect[1];
	family = 1;
	rlvect(rvect, lvect, family, matrix, lambda, num_real_roots);
	evects(0,1) = rvect[0];
	evects(1,1) = rvect[1];
}

