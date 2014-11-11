#include <cmath>
#include <iostream>
#include "eigen.h"

static int
orthog(double x, double y, double &vect0, double &vect1)
{
	double norm;
	double mcheps = 1.e-5;
	int orth = 0;

	norm = x*x + y*y;
	if (norm <= mcheps*mcheps)
		return orth;
	norm = std::sqrt(norm);
	orth = 1;

	vect0 = -y/norm;
	vect1 = x/norm;

	return orth;
}

static int
diagon(double *lambda, double evect[2][2], double matrix[2][2],
		int num_real_roots, int fam)
{
	int id, other, k;
	double eps = 1.e-5;

	if (num_real_roots > 1)		// 2 distinct eigenvalues
		for (k=0; k<2; k++)
		{
			other = (k+1) % 2;
			id = orthog(matrix[0][0]-lambda[fam],
				matrix[k][other],evect[k][0], evect[k][1]);
			if (id == 0)
				id = orthog(matrix[other][k],
					matrix[1][1]-lambda[fam], evect[k][0],
					evect[k][1]);
		}
	else if (num_real_roots == 1)	// 2 equal eigenvalues
	{
		if ((matrix[0][1]*matrix[0][1] < eps*lambda[0]*lambda[0]) &&
			(matrix[1][0]*matrix[1][0] < eps*lambda[1]*lambda[1]))
		{
			// matrix is a multiple of the identity
			evect[0][0] = 1.;
			evect[0][1] = 0.;
			evect[1][0] = 0.;
			evect[1][1] = 1.;
			num_real_roots = 3;
			return num_real_roots;
		}
		else
		{
			for (k=0; k<2; k++)
			{
				other = (k+1) % 2;
				id = orthog(matrix[0][0]-lambda[0],
					matrix[k][other],evect[k][0],
					evect[k][1]);
				if (id == 0)
					id = orthog(matrix[other][k],
						matrix[1][1]-lambda[0],
						evect[k][0], evect[k][1]);
			}
			if (id == 1) return num_real_roots;

			// matrix is a multiple of the identity
			evect[0][0] = 1.;
			evect[0][1] = 0.;
			evect[1][0] = 0.;
			evect[1][1] = 1.;
			num_real_roots = 3;
			return num_real_roots;

		}
	}
	else		// eigenvalues are complex conjugates
	{
		std::cerr << "ERROR: In elliptic region\n";
	}
	return num_real_roots;
}

int
eigval(double lambda[2], double matrix[2][2])
{
	double tr = matrix[0][0] + matrix[1][1];
	double det = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

	return quadratic_roots(1.0, -tr, det, lambda);
}

void
rlvect(double *rvect, double *lvect, int family, double matrix[2][2],
		double *lambda, int num_real_roots)
{
	int rl;
	double evectr[2][2];

	rl = diagon(lambda, evectr, matrix, num_real_roots, family);
	if (rl == 0)
		return;

	rvect[0] = evectr[0][0];
	rvect[1] = evectr[0][1];
	lvect[0] = evectr[1][0];
	lvect[1] = evectr[1][1];

	if ((rvect[0]*lvect[0] + rvect[1]*lvect[1]) < 0.)
	{
		lvect[0] = -1.*lvect[0];
		lvect[1] = -1.*lvect[1];
	}
	return;
}
