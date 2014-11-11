#ifndef _eigen_h
#define _eigen_h

#include "polyroot.h"

/*
*  eigval() calculates the eigenvalues of "matrix"; its return value
*  is the number of real roots, as found by quadratic_roots() applied
*  to the characteristic polynomial (see polyroot.h)
*/

int
eigval(double lambda[2], double matrix[2][2]);


/*
*  rlvect() calculates the right and left eigenvectors of "matrix".
*  In the argument list, "lambda" and "num_real_roots" should come
*  from eigval(), and "family" is the eigenvalue family (0 or 1).
*/

void
rlvect(double *rvect, double *lvect, int family, double matrix[2][2],
	double *lambda, int num_real_roots);

#endif /* _eigen_h */
